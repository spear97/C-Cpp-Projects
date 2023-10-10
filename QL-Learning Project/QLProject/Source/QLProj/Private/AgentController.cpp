// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentController.h"

AAgentController::AAgentController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	//Generate the Matrix that will be used by the Agent
	GenerateMatrix();

	//The Timer that will act as the Driver for the Q_Learning Algorithm
	GetWorldTimerManager().SetTimer(Timer, this, &AAgentController::Q_Learning, delay, true);
}

// Called when the Controller is Destroyed
void AAgentController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//Create file
	ofstream file;

	//Open a text file
	file.open(GetFileDirectory("NodeScoreNums"), std::ios::trunc);

	//Store Data to file
	for (int i = 0; i < Q.Num(); i++)
	{
		for (int j = 0; j < Q[i].Num(); j++)
		{
			file << Q[i][j] << " ";
		}

		file << endl;
	}

	// Close the file
	file.close();
}

// Called every frame
void AAgentController::Tick(float delta)
{
	Super::Tick(delta);

	s = GetState();
	a = GetAction();
}

//Generate the Matrix that will be used for Q-Learning
void AAgentController::GenerateMatrix()
{
	//Get All WayPoints in the Environment
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), WayPoints);

	//Set State Size as WayPoints
	s_size = WayPoints.Num();

	//Set Action Size to 8 for Directions AI Agent can move in
	a_size = 8;

	//Check if file contain NodeScoreNums Already Exists, if so then extract data from file and store it in Q
	if (FileExists(GetFileDirectory("NodeScoreNums")))
	{
		//Create file
		ifstream file;

		//Open a text file
		file.open(GetFileDirectory("NodeScoreNums"));

		//the line that is being read
		string line;

		//Read through file
		while (getline(file, line))
		{
			//Convert Line into a TArray<FString>
			TArray<FString> data = Split(line);

			//Convert each FString into a float
			TArray<float> new_line;
			for (int i = 0; i < data.Num(); i++)
			{
				new_line.Add(FCString::Atof(*data[i]));
			}

			//Append the Result to Q
			Q.Add(new_line);
		}
	}
	else CreateMatrix();
}

//Create a Martix if data neither exists or can't be extracted
void AAgentController::CreateMatrix()
{
	for (int i = 0; i < s_size; i++)
	{
		TArray<float> T; //The TArray that will be appended to Q

		int k = i % a_size; //Get the module of current value of i by a_size (number actions) to iterate through R

		//Populate Data Values into T based on Data found from R
		for (int j = 0; j < a_size; j++)
		{
			T.Add(R[k][j]);
		}

		Q.Add(T); //Append T to Q
	}

	ofstream file(GetFileDirectory("NodeScoreNums")); //Create File to Store Data in
	file.close(); //Close File to prevent data leakage
}

//Output the Matrix to the Screen, Used for Debugging Purposes
void AAgentController::PrintMatrix()
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, FString::Printf(TEXT("-------------------------"))); }

	for (int i = s_size - 1; i >= 0; i--)
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, FString::Printf(TEXT("|%f %f %f %f %f %f %f %f|"), Q[i][0], Q[i][1], Q[i][2], Q[i][3], Q[i][4], Q[i][5], Q[i][6], Q[i][7])); }
	}

	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, FString::Printf(TEXT("-------------------------"))); }
}

//Get the Current State that the Agent is in
int AAgentController::GetState()
{
	FVector AgentLocation = this->GetPawn()->GetActorLocation();
	float nearest = INFINITY;
	int nearestIndex = NULL;

	for (int i = 0; i < WayPoints.Num(); i++)
	{
		float dist = FVector::Dist(WayPoints[i]->GetActorLocation(), AgentLocation);
		if (dist < nearest) { nearest = dist; nearestIndex = i; }
	}

	return nearestIndex;
}

//Get the Best Action for Current State
int AAgentController::GetAction()
{
	float bestScore = -INFINITY;
	float bestIndex = NULL;

	for (int i = 0; i < Q[s].Num(); i++)
	{
		if (Q[s][i] > bestScore)
		{
			bestScore = Q[s][i];
			bestIndex = i;
		}
	}

	return bestIndex;
}

//The Function that will the Reinforcement Learning for the Agent
void AAgentController::Q_Learning()
{
	//Perform for the current value
	switch (a)
	{
	case 0:
		Fwd();
		break;
	case 1:
		FwdRt();
		break;
	case 2:
		Rt();
		break;
	case 3:
		BwdRt();
		break;
	case 4:
		Bwd();
		break;
	case 5:
		BwdLt();
		break;
	case 6:
		Lt();
		break;
	case 7:
		FwdLt();
		break;
	}

	//Check if Target Exists
	//Target is Needed for Reinforcement Learning to Operate
	if (Target)
	{
		float currDist = FVector::Dist(Target->GetActorLocation(), this->GetPawn()->GetActorLocation());

		if (currDist < prevDist)
		{
			r = 1;
			prevDist = currDist;
		}
		else
		{
			r = -5;
			prevDist = currDist;
		}

		Q[s][a] = CalculatePolicy();
	}
}

//Get the Score for the Correspond Action and State
float AAgentController::CalculatePolicy()
{
	return Q[s][a] + alpha * (r + gamma * GetMaxQ() - Q[s][a]);
}

//Get the Maximum Score for the Given State
float AAgentController::GetMaxQ()
{
	//The Current Row that is being Analyzed
	TArray<float> T = Q[s];

	//The maximum score for the Analyzed Row
	float max = -INFINITY;

	//Iterate through the current Row
	for (int i = 0; i < T.Num(); i++)
	{
		//If the current element is greater than max, then updated max
		if (T[i] > max)
		{
			max = T[i];
		}
	}

	//Return the maximum value
	return max;
}

//Move the Agent Forward -> 0
void AAgentController::Fwd()
{
	MoveToLocation(GetPawn()->GetActorLocation() + (GetPawn()->GetActorForwardVector() * 250.f));
}

//Move the Agent Forward-Right -> 1
void AAgentController::FwdRt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + ((GetPawn()->GetActorForwardVector() * 250.f) + (GetPawn()->GetActorRightVector() * 250.f)));
}

//Move the Agent Right -> 2
void AAgentController::Rt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + (GetPawn()->GetActorRightVector() * 250.f));
}

//Move the Agent Backward-Right -> 3
void AAgentController::BwdRt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + ((-GetPawn()->GetActorForwardVector() * 250.f) + (GetPawn()->GetActorRightVector() * 250.f)));
}

//Move the Agent Backward -> 4
void AAgentController::Bwd()
{
	MoveToLocation(GetPawn()->GetActorLocation() + (-GetPawn()->GetActorForwardVector() * 250.f));
}

//Move the Agent Backward-Left -> 5
void AAgentController::BwdLt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + ((-GetPawn()->GetActorForwardVector() * 250.f) + (-GetPawn()->GetActorRightVector() * 250.f)));
}

//Move the Agent left -> 6 
void AAgentController::Lt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + (-GetPawn()->GetActorRightVector() * 250.f));
}

//Move the Agent Forward-Left -> 7
void AAgentController::FwdLt()
{
	MoveToLocation(GetPawn()->GetActorLocation() + ((GetPawn()->GetActorForwardVector() * 250.f) + (-GetPawn()->GetActorRightVector() * 250.f)));
}

//Get a Row of Data from Q at given Index of Q ranging from 0 to N-1
FString AAgentController::GetQAtIndex(int Index)
{
	//Copy of the Array Stored in Q at the Given Index
	TArray<float> Copy = Q[Index];

	//The Result that will be returned
	FString Result;

	//Format Resulting String
	Result.Append("|");
	for (int i = 0; i < Copy.Num(); i++)
	{
		float x = round(Copy[i]);
		Result.Append(FString::SanitizeFloat(x));
		if (i < Copy.Num() - 1) Result.Append(" ");
	}
	Result.Append("|");

	return Result;
}

//Return the Label for the Row Row of Dat that is Extracted
FString AAgentController::GetQActionLabel()
{
	return "\t\t\tFwd FwdRt Rt BwdRt Bwd BwdLt Lt FwdLt";
}

//Check if a File Exists
inline bool AAgentController::FileExists(const string& name) 
{
	if (FILE* file = fopen(name.c_str(), "r")) 
	{
		fclose(file);
		return true;
	}
	else 
	{
		return false;
	}
}

//Convert Unreal File Directory from FString to String
string AAgentController::GetFileDirectory(FString filename)
{
	return TCHAR_TO_UTF8(*(FPaths::ProjectDir() + filename + ".txt"));
}

//Split pass String and split it into segments
TArray<FString> AAgentController::Split(string x)
{
	//The collection of data for string x that will be returned
	TArray<FString> collection;
	
	//Convert std::string to FString
	FString str(x.c_str());

	//The Element that is being read and generated
	FString data = "";

	//Iterate through the bassed string, 
	for (int i = 0; i < str.Len(); i++)
	{
		if (str[i] == ' ')
		{
			collection.Add(data);
			data = "";
		}
		else
		{
			data += str[i];
		}
	}
	return collection;
}

//Check if a given file is empty or not
bool AAgentController::isFileEmpty(const string& filename)
{
	ifstream file(filename);
	return file.peek() == ifstream::traits_type::eof();
}

//Round a passed variable to 2 decimal places
float AAgentController::round(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}