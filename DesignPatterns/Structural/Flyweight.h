/* Flyweights are used to share expensive objects more efficiently
 *
 * "Designing objects down to the lowest levels of system "granularity" provides
 * optimal flexibility, but can be unacceptably expensive in terms of performance
 * and memory usage"
 * 
 * Example: when loading a website, there are many images. For every new image,
 * the image is loaded and cached. For any consequent instances that uses the same
 * image, a flyweight with cached image is used rather than loading a duplicate image.
 * The created flyweights might have different data attached such as different
 * position or size of the image.
 * 
 * The original cached object is the INTRINSIC part, and the extra data is the
 * EXTRINSIC part that can't be shared and is unique.
 * 
 * Checklist:
 * 1. Ensure object overhead is actually an issue, and the client is willing to use
 *    factories to get flyweights
 * 2. Divide target class into sharable (intrinsic) and non-sharable(extrinsic)
 * 3. Remove extrinsic parts from class attributes, make it a parameter to be passed
 * 4. Create factory that cache and reuse class
 * 5. Client must use factory instead of `new`
 * 6. Client must look-up or compute the extrinsic stuff and supply it to the class
 * 
 */

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

// [OPTIONAL: instead of using string to access cache, we can hash it]
int getStringHash(const std::string& str)
{
	// Starting with prime number
	int hash = 13;

	for (int i = 0; i < str.length(); i++)
	{
		hash = hash * 101 + str[i];
	}

	return hash;
}

// Suppose we have this texture class that's being used everywhere
// It holds a reference to a texture path and displays a texture
class Texture
{
public:
	Texture(std::string path) { m_texturePath = path; }
	void setSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

	// Extrinsic states are passed via parameters
	void display(int x, int y)
	{
		std::cout << "Displaying image " << m_texturePath;
		std::cout << " [" << m_width << "x" << m_height << "] ";
		std::cout << "at (x,y)=(" << x << "," << y << ").\n";
	}

protected:

	// All of these are intrinsic states
	std::string m_texturePath;
	int m_width;
	int m_height;
};

// If multiple instances of this class is used, we can create a flyweight factory for this class
class TextureFlyweightFactory
{
public:

	// Factory get instance
	static Texture* getTexture(const std::string& path, int width, int height)
	{
		// First we check if we already have existing texture class to share
		const int textureKey = getStringHash(path);
		if (m_cachedTexturesMap.find(textureKey) == m_cachedTexturesMap.end())
		{
			// Does not exist
			Texture *newTexture = new Texture(path);
			newTexture->setSize(width, height);
			m_cachedTexturesMap[textureKey] = newTexture;

			std::cout << "Creating new texture\n";

			return newTexture;
		}
		else
		{
			// Exist, return object
			std::cout << "Reusing texture\n";

			return m_cachedTexturesMap[textureKey];
		}
	}

private:

	// We can also use a vector if the key is stored inside the object itself
	static std::unordered_map<int, Texture*> m_cachedTexturesMap;

};

// How it's used ???
namespace flyweight
{
	void example()
	{
		std::string path1 = "ball.jpg";
		std::string path2 = "background.png";

		// Create some stuff
		Texture* texture1 = TextureFlyweightFactory::getTexture(path1, 100, 200);
		Texture* texture2 = TextureFlyweightFactory::getTexture(path2, 800, 600);

		// Expecting reusing texture
		Texture *texture3 = TextureFlyweightFactory::getTexture(path1, 50, 50);
		Texture *texture4 = TextureFlyweightFactory::getTexture(path1, 20, 20);

		texture1->display(50, 50);
		texture2->display(0, 0);
		texture3->display(100, 0);
		texture4->display(0, 100);
	}
}