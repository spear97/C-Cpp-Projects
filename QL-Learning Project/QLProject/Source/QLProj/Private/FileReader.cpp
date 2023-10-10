// Fill out your copyright notice in the Description page of Project Settings.


#include "FileReader.h"

bool UFileReader::LoadTxt(FString FileName, FString& SaveText)
{
	return FFileHelper::LoadFileToString(SaveText, *(FPaths::ProjectDir() + FileName));
}

bool UFileReader::SaveTxt(FString SaveText, FString FileName)
{
	return FFileHelper::SaveStringToFile(SaveText, *(FPaths::ProjectDir() + FileName));
}