#ifndef GUMIGOTA_VERTEXBUFFER_H
#define GUMIGOTA_VERTEXBUFFER_H



namespace gg
{

	/* ADDITIONAL STUFF */
	enum VertexBufferDrawType
	{
		VERTEX_BUFFER_STATIC_DRAW = 0, //good for data that isnt modified
		VERTEX_BUFFER_DYNAMIC_DRAW,
		VERTEX_BUFFER_STREAM_DRAW  //good for data that is often modified
	};



	class VertexBuffer
	{
	private:
		/* Variables */
		unsigned int m_id;
		unsigned int m_componentCount;

	public:
		/* Constructors */
		VertexBuffer(const void* data, const unsigned int size, const unsigned int componentCount); //size is in floats amount
		VertexBuffer(const void* data, const unsigned int size, const unsigned int componentCount, VertexBufferDrawType usage); //size is in floats amount

		/* Destructor */
		~VertexBuffer();

		/* Functions */
		void bufferData(const void* data, const unsigned int size); //size is in floats amount
		void bufferData(const void* data, const unsigned int size, VertexBufferDrawType usage); //size is in floats amount
		void bufferSubData(const void* data, const unsigned int size); //size is in floats amount

		void bind() const;
		static void unbind();

		// Getters
		inline unsigned int getID() const { return m_id; };
		inline unsigned int getComponentCount() const { return m_componentCount; };

	};

}


#endif