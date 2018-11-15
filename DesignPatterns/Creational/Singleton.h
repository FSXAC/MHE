/* Use singleotn when we one and only one instance of an object
 *
 * Checklist:
 * 		- private static member to hold the single instance
 * 		- public static method to get the instance
 * 		- private or protected constructors
 * 		- lazy initialization (creation on first use)
 */

#include <iostream>

// i.e. we want to have an achievement tracker, but the entire game should only have one
class AchievementTracker
{
public:
	// public static method getter
	static AchievementTracker* getInstance()
	{
		// Lazy initialization
		if (!m_instance)
		{
			m_instance = new AchievementTracker();
		}

		return m_instance;
	}

	// Other stuff
	void reset() { m_counter = 0; }
	void increment(int value) { m_counter += value; }
	bool getAchievementUnlocked() { return m_counter >= 5; }

private:
	// Private constructor
	AchievementTracker()
	{
		m_counter = 0;
	}

private:
	// Private static member to hold the single instance
	static AchievementTracker* m_instance;
	int m_counter;
};


// How it's used ???
namespace singleton
{
	// Suppose we have two classes (enemies) and both will interact with the achievement
	class MonsterSpawner
	{
	public:
		MonsterSpawner() = default;
		void kill()
		{
			AchievementTracker::getInstance()->increment(3);
		}
	};

	class DiamondMine
	{
	public:
	  DiamondMine() = default;
	  void mine()
	  {
		  AchievementTracker::getInstance()->increment(1);
		}
	};

	void example() {
		MonsterSpawner spawner;
		DiamondMine mineshaft;

		spawner.kill();
		std::cout << AchievementTracker::getInstance()->getAchievementUnlocked() << std::endl;
		// expecting false

		mineshaft.mine();
		std::cout << AchievementTracker::getInstance()->getAchievementUnlocked() << std::endl;
		// expecting false

		mineshaft.mine();
		std::cout << AchievementTracker::getInstance()->getAchievementUnlocked() << std::endl;
		// expecting true
	}
}