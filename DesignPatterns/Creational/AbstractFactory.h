#pragma once


#include <iostream>

// !!! Assume we have the following class hiearchy
class Loot
{
public:
	virtual int getValue();
};

class Gold : public Loot
{
public:
	int getValue() override
	{
		return 24;
	}
};

class Diamond : public Loot
{
public:
	int getValue() override
	{
		return 50;
	}
};

// !!! Interfaces to the loot
class Miner
{
public:
	virtual int getSkillLevel();
};

// Derived class from interface
class GoldMiner : public Miner
{
public:
	int getSkillLevel() override { return 2; }
};

class DiamondMiner : public Miner
{
public:
	int getSkillLevel() override { return 5; }
};

// !!! Factory to create loot and miner
class LootFactory
{
public:
	virtual Loot *makeLoot();
	virtual Miner* makeMiner();
};

class GoldFactory : public LootFactory
{
public:
	Loot *makeLoot() override { return new Gold(); }
	Miner *makeMiner() override { return new GoldMiner(); }
};

class DiamondFactory : public LootFactory
{
public:
	Loot *makeLoot() override { return new Diamond(); }
	Miner *makeMiner() override { return new DiamondMiner(); }
};

// How is it used ???
namespace abstract_factory
{
	void example()
	{
		Loot* loot;
		Miner* miner;

		// Gold
		auto goldFactory = new GoldFactory();
		loot = goldFactory->makeLoot();
		miner = goldFactory->makeMiner();

		std::cout << "Gold value: " << loot->getValue() << ", miner skill: " << miner->getSkillLevel() << "\n";

		// Diamond
		auto diamondFactory = new DiamondFactory();
		loot = diamondFactory->makeLoot();
		miner = diamondFactory->makeMiner();

		std::cout << "Diamond value: " << loot->getValue() << ", miner skill: " << miner->getSkillLevel() << "\n";
	}
}