#ifndef GUMIGOTA_PARTICLE_GROUP_H
#define GUMIGOTA_PARTICLE_GROUP_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "Particle.h"



namespace gg
{

	class ParticleGroup
	{
	private:
		/* Variables */
		std::vector<Particle> m_particles;
		Texture* m_texture;
		unsigned int m_startingTextureAtlasIndex, m_endingTextureAtlasIndex;
		unsigned int m_texturePhaseCount; //tells how many "sub-textures" texture atlas cointains
		std::vector<vector2> m_textureOffsets; //stores texture offsets for every index of texture atlas

		bool m_usingAdditiveBlending; //if true particles will be rendered using additive blending; if false particles will be rendered normally
		bool m_sortParticles; //if true partices will be sorted from the closest to the furthest from camera; if false particles will not be sorted (increased performance) if m_usingAdditiveBlending is true, particles will not be sorted anyway

	public:
		/* Constructors */
		ParticleGroup(Texture* texture);
		ParticleGroup(Texture* texture, const bool additiveBlending);
		ParticleGroup(Texture* texture, const bool additiveBlending, const bool sortParticles);
		ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex);
		ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex, const bool additiveBlending);
		ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex, const bool additiveBlending, const bool sortParticles);

		/* Functions */
		void update(const Camera3D& cam);

		void add(const Particle& particle);
		void popBack();
		void reserve(const unsigned int amount);

		void bind() const;
		static void unbind();

		// Setters
		void setUsingAdditiveBlending(const bool value);
		void setSortParticles(const bool value);

		// Getters
		const std::vector<Particle>& getParticles() const { return m_particles; }
		const std::vector<vector2>& getTextureOffsets() const { return m_textureOffsets; }

		bool usingAdditiveBlending() const { return m_usingAdditiveBlending; }

		unsigned int getTextureAtlasRows() const { return m_texture->getAtlasRows(); }
		unsigned int getTexturePhaseCount() const { return m_texturePhaseCount; }

	private:
		// Private Functions
		void m_init();

		void m_sortParticlesByDistance();

	};

}



#endif