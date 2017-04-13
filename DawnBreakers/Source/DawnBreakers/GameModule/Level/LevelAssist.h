// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DAWNBREAKERS_API LevelAssist
{
public:
	LevelAssist();
	~LevelAssist();

	void OpenStoryModeLevel(const FName& StoryLevelName);

	void OpenMultiplayerLevel(const FName& LevelName);

	void Clear();

};
