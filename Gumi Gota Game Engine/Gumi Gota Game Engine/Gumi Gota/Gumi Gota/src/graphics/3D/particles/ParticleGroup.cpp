
/* INCLUDES */
// Self Include
#include "ParticleGroup.h"



/* MACROS */
#define PARTICLE_GROUP_DEFAULT_USING_ADDITIVE_BLENDING false
#define PARTICLE_GROUP_DEFAULT_SORT_PARTICLES true



namespace gg
{

	/* Constructors */
	ParticleGroup::ParticleGroup(Texture* texture)
		: m_texture(texture), m_startingTextureAtlasIndex(0), m_endingTextureAtlasIndex(texture->getAtlasRows() * texture->getAtlasRows() - 1),
		  m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
	      m_usingAdditiveBlending(PARTICLE_GROUP_DEFAULT_USING_ADDITIVE_BLENDING), m_sortParticles(PARTICLE_GROUP_DEFAULT_SORT_PARTICLES)
	{
		m_init();
	}

	ParticleGroup::ParticleGroup(Texture* texture, const bool additiveBlending)
		: m_texture(texture), m_startingTextureAtlasIndex(0), m_endingTextureAtlasIndex(texture->getAtlasRows() * texture->getAtlasRows() - 1),
		  m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
		  m_usingAdditiveBlending(additiveBlending), m_sortParticles(PARTICLE_GROUP_DEFAULT_SORT_PARTICLES)
	{
		m_init();
	}

	ParticleGroup::ParticleGroup(Texture* texture, const bool additiveBlending, const bool sortParticles)
		: m_texture(texture), m_startingTextureAtlasIndex(0), m_endingTextureAtlasIndex(texture->getAtlasRows() * texture->getAtlasRows() - 1),
		  m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
		  m_usingAdditiveBlending(additiveBlending), m_sortParticles(sortParticles)
	{
		m_init();
	}

	ParticleGroup::ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex)
		: m_texture(texture), m_startingTextureAtlasIndex(startIndex), m_endingTextureAtlasIndex(endIndex),
		  m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
		  m_usingAdditiveBlending(PARTICLE_GROUP_DEFAULT_USING_ADDITIVE_BLENDING), m_sortParticles(PARTICLE_GROUP_DEFAULT_SORT_PARTICLES)
	{
		m_init();
	}

	ParticleGroup::ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex, const bool additiveBlending)
		: m_texture(texture), m_startingTextureAtlasIndex(startIndex), m_endingTextureAtlasIndex(endIndex),
		  m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
		  m_usingAdditiveBlending(additiveBlending), m_sortParticles(PARTICLE_GROUP_DEFAULT_SORT_PARTICLES)
	{
		m_init();
	}

	ParticleGroup::ParticleGroup(Texture* texture, const unsigned int startIndex, const unsigned int endIndex, const bool additiveBlending, const bool sortParticles)
		: m_texture(texture), m_startingTextureAtlasIndex(startIndex), m_endingTextureAtlasIndex(endIndex),
		m_texturePhaseCount(m_texture->getAtlasRows() * m_texture->getAtlasRows()),
		m_usingAdditiveBlending(additiveBlending), m_sortParticles(sortParticles)
	{
		m_init();
	}

	/* Functions */
	void ParticleGroup::update(const Camera3D& cam)
	{
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			// Transition Stuff Updating
			unsigned int phaseCount = m_endingTextureAtlasIndex - m_startingTextureAtlasIndex + 1;
			m_particles[i].updateTransitionStuff(phaseCount, m_startingTextureAtlasIndex);

			// Checking if Particle's Lifetime is Over
			if (!m_particles[i].update(cam))
			{
				// Deleting Particle
				m_particles.erase(m_particles.begin() + i);
			}
		}

		// Sorting Particles by Distances From Camera
		if (m_sortParticles && !m_usingAdditiveBlending)
			m_sortParticlesByDistance();
	}


	void ParticleGroup::add(const Particle& particle)
	{
		m_particles.push_back(particle);
	}

	void ParticleGroup::popBack()
	{
		m_particles.pop_back();
	}

	void ParticleGroup::reserve(const unsigned int amount)
	{
		m_particles.reserve(amount);
	}


	void ParticleGroup::bind() const
	{
		m_texture->bind();
	}

	void ParticleGroup::unbind()
	{
		Texture::unbind();
	}

	// Setters
	void ParticleGroup::setUsingAdditiveBlending(const bool value)
	{
		m_usingAdditiveBlending = value;
	}

	void ParticleGroup::setSortParticles(const bool value)
	{
		m_sortParticles = true;
	}

	// Private Functions
	void ParticleGroup::m_init()
	{
		// Texture Offset Setup
		if (m_texture->getAtlasRows() == 1) // Single Texture
		{
			m_textureOffsets.reserve(1);
			m_textureOffsets.push_back(vector2(0.0f));
		}
		else // Texture Atlas
		{
			// Init
			m_textureOffsets.reserve(m_texturePhaseCount);

			vector2 singleSquareSize(1.0f / m_texture->getAtlasRows());

			// Calculating Offsets
			for (unsigned int y = 0; y < m_texture->getAtlasRows(); y++)
			{
				for (unsigned int x = 0; x < m_texture->getAtlasRows(); x++)
				{
					m_textureOffsets.push_back(vector2(singleSquareSize.x * x, singleSquareSize.y * y));
				}
			}

		}
	}


	void ParticleGroup::m_sortParticlesByDistance()
	{
		// Insert Sort
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			int partitionIndex = 0;

			for (unsigned int j = i; j > 0; j--)
			{
				if (m_particles[i - partitionIndex].getDistanceFromCamera() > m_particles[j - 1].getDistanceFromCamera())
				{
					// Swapping Particles
					Particle particleCopy = m_particles[i - partitionIndex];
					m_particles[i - partitionIndex] = m_particles[j - 1];
					m_particles[j - 1] = particleCopy;

					// Raising Partition Index
					partitionIndex++;
				}
			}
		}
	}

}