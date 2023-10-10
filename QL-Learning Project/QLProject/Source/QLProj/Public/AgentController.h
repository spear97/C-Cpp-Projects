// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WayPoint.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "AgentController.generated.h"

/**
 * 
 */

using namespace std;

UCLASS()
class QLPROJ_API AAgentController : public AAIController
{
	GENERATED_BODY()

	//Debugging Matrix
	#define DisplayNum(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%i"), x));}
	#define DisplayRow() if(GEngine){GEngine->AddOnScreenDebugMessage(-1, delay, FColor::White, FString::Printf(TEXT("State: %i |%f %f %f %f %f %f %f %f|"), s, Q[s][0], Q[s][1], Q[s][2], Q[s][3], Q[s][4], Q[s][5], Q[s][6], Q[s][7]));}
	
public:

	//Constructor for the Class
	AAgentController();

	/**************Blueprint Functions****************/

	//Get one of the Lists of the Q-Matrix
	UFUNCTION(BlueprintCallable)
	FString GetQAtIndex(int Index);

	UFUNCTION(BlueprintCallable)
	FString GetQActionLabel();

	/**************The Initial Variables for the Q-Learning**************/

	//The Number of States for the Matrix
	UPROPERTY(BlueprintReadOnly)
	int s_size;

	//The Number of Actions for the Matrix
	UPROPERTY(BlueprintReadOnly)
	int a_size;

	//The Current State that the Agent is currently in
	UPROPERTY(BlueprintReadOnly)
	int s;

	//The Current Action that the Agent is Performing for the Given State
	UPROPERTY(BlueprintReadOnly)
	int a;

	//The Reward for the Action that was given 
	UPROPERTY(BlueprintReadOnly)
	int r;

	//The Learning Discount for the Policy
	UPROPERTY(BlueprintReadOnly)
	float alpha = 0.95f;

	//The Discount Factor for the Policy
	UPROPERTY(BlueprintReadOnly)
	float gamma = 0.95f;

	/***************Action Variables***************/

	//How Far was Agent from Target on Previous Action
	UPROPERTY(BlueprintReadOnly)
	float prevDist = INFINITY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the Controller is Destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float delta) override;

protected:

	/**************The Initial Function for the Q-Learning**************/

	//Generate the Matrix that will be used for Q-Learning
	void GenerateMatrix();

	//Create a Martix if data neither exists or can't be extracted
	void CreateMatrix();

	//Output the Matrix to the Screen, Used for Debugging Purposes
	void PrintMatrix();

	/*****************Q-Learning Reinforcement Functions**************/

	//Get the Current State that the Agent is in
	int GetState();

	//Get the Best Action for Current State
	int GetAction();

	//Run Reinforcement Learning Model
	void Q_Learning();

	//Get the Score for the Correspond Action and State
	float CalculatePolicy();

	//Get the Maximum Score for the Given State
	float GetMaxQ();

	/************The Action Functions that the Agent Can take************/

	//Move the Agent Forward -> 0
	void Fwd();

	//Move the Agent Forward-Right -> 1
	void FwdRt();

	//Move the Agent Right -> 2
	void Rt();

	//Move the Agent Backward-Right -> 3
	void BwdRt();

	//Move the Agent Backward -> 4
	void Bwd();

	//Move the Agent Backward-Left -> 5
	void BwdLt();

	//Move the Agent left -> 6 
	void Lt();

	//Move the Agent Forward-Left -> 7
	void FwdLt();

	/******FIle I/O Functions******/

	//Does a file of a given name exist in the directory
	inline bool FileExists(const string& name);

	//Return the file path to the file in String Format
	//Allow for path to be OS Agnostic
	string GetFileDirectory(FString filename);

	//Split pass String and split it into segments
	TArray<FString> Split(string x);

	//Check if a given file is empty or not
	bool isFileEmpty(const string& filename);

	/*******Other Functions*******/

	//Round a floating-point number to 2 decimal places
	float round(float var);

public:

	/**************Variables that will get set in Blueprint**************/
	UPROPERTY(BlueprintReadWrite)
	AActor* Target;

protected:
	/**************The Initial Variables for the Q-Learning**************/

	//All WayPoints that exist in the Environment
	TArray<AActor*> WayPoints;

	//The Matrix for Q-Learning to Operate
	TArray<TArray<float>> Q;

	//The Reward Matrix that will initially Populate the Q Matrix
	TArray<TArray<float>> R = {
		{-1.f, -1.f, -1.f, -1.f,  0.f,  -1.f,  0.f,  -1.f},
		{-1.f, -1.f, -1.f,  0.f, -1.f, 100.f, -1.f, 100.f},
		{-1.f, -1.f, -1.f,  0.f, -1.f,  -1.f, -1.f,  -1.f},
		{-1.f,  0.f,  0.f, -1.f,  0.f,  -1.f,  0.f,  -1.f},
		{ 0.f, -1.f, -1.f,  0.f, -1.f, 100.f, -1.f, 100.f},
		{-1.f,  0.f, -1.f, -1.f,  0.f, 100.f,  0.f, 100.f},
		{-1.f, -1.f, -1.f, -1.f,  0.f,  -1.f,  0.f,  -1.f},
		{-1.f, -1.f, -1.f,  0.f, -1.f, 100.f, -1.f, 100.f}
	};

	/**************Operational Variables**************/

	//Timer Handler that will Aid in Running the Q_Learning Algorithm
	FTimerHandle Timer;

	//The time duration that the time will run for
	float delay = 0.5f;

	/***************Action Variables***************/

	//How far the Agent can move for any given direction
	float move_dist = 250.f;
};