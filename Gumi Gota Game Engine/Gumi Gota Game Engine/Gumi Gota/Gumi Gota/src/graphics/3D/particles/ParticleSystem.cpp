
/* INCLUDES */
// Self Include
#include "ParticleSystem.h"



/* MACROS */
#define PARTICLE_SYSTEM_DEFAULT_USING_ADDITIVE_BLENDING false
#define PARTICLE_SYSTEM_DEFAULT_SORT_PARTICLES true



namespace gg
{

	/* Contructors */
	ParticleSystem::ParticleSystem(Texture* texture)
		: m_texture(texture), 
		  m_startingTextureAtlasIndex(0), m_endingTextureAtlasIndex(texture->getAtlasRows() * texture->getAtlasRows() - 1),
		  m_usingAdditiveBlending(PARTICLE_SYSTEM_DEFAULT_USING_ADDITIVE_BLENDING), m_sortParticles(PARTICLE_SYSTEM_DEFAULT_SORT_PARTICLES)
	{}

	/* Functions */
	void ParticleSystem::setStartingTextureAtlasIndex(const unsigned int index)
	{
		m_startingTextureAtlasIndex = index;
	}

	void ParticleSystem::setEndingTextureAtlasIndex(const unsigned int index)
	{
		m_endingTextureAtlasIndex = index;
	}

	void ParticleSystem::setTextureAtlasIndices(const unsigned int startIndex, const unsigned int endIndex)
	{
		m_startingTextureAtlasIndex = startIndex;
		m_endingTextureAtlasIndex = endIndex;
	}


	void ParticleSystem::setUsingAdditiveBlending(const bool value)
	{
		m_usingAdditiveBlending = value;
	}

	void ParticleSystem::setSortParticles(const bool value)
	{
		m_sortParticles = true;
	}

}