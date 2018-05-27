#ifndef GUMIGOTA_INDEXBUFFER_H
#define GUMIGOTA_INDEXBUFFER_H



namespace gg
{

	/* ADDITIONAL STUFF */
	enum IndexBufferDrawType
	{
		INDEX_BUFFER_DRAW_STATIC = 0,
		INDEX_BUFFER_DRAW_DYNAMIC
	};



	class IndexBuffer
	{
	private:
		/* Variables */
		unsigned int m_id;
		unsigned int m_count;

	public:
		/* Constructors */
		IndexBuffer(const unsigned int* data, const unsigned int count);
		IndexBuffer(const unsigned int* data, const unsigned int count, IndexBufferDrawType usage);

		/* Destructor */
		~IndexBuffer();

		/* Functions */
		void bufferData(const unsigned int* data, const unsigned int count);
		void bufferData(const unsigned int* data, const unsigned int count, IndexBufferDrawType usage);

		void bind() const;
		static void unbind();

		// Getters
		inline unsigned int getCount() const { return m_count; }

	};

}



#endif