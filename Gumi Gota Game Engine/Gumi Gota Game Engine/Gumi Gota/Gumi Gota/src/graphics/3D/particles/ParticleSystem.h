#ifndef GUMIGOTA_PARTICLE_SYSTEM_H
#define GUMIGOTA_PARTICLE_SYSTEM_H



/* INCLUDES */
// Header Includes
#include "ParticleGroup.h"



namespace gg
{

	class ParticleSystem
	{
	protected:
		/* Variables */
		Texture* m_texture;
		unsigned int m_startingTextureAtlasIndex, m_endingTextureAtlasIndex;

		bool m_usingAdditiveBlending; //if true particles from generated groups will be rendered using additive blending; if false particles from generated groups will be rendered using alpha blending
		bool m_sortParticles; //if true partices will be sorted from the closest to the furthest from camera; if false particles will not be sorted (increased performance) if m_usingAdditiveBlending is true, particles will not be sorted anyway

	public:
		/* Contructors */
		ParticleSystem(Texture* texture);

		/* Functions */
		// Pure Virtual Functions
		virtual ParticleGroup generateParticles(const vector3& center, const unsigned int amount) = 0; //center is a position where particles are coming from

		// Setters
		void setStartingTextureAtlasIndex(const unsigned int index);
		void setEndingTextureAtlasIndex(const unsigned int index);
		void setTextureAtlasIndices(const unsigned int startIndex, const unsigned int endIndex);

		void setUsingAdditiveBlending(const bool value);
		void setSortParticles(const bool value);

	};

}



#endif