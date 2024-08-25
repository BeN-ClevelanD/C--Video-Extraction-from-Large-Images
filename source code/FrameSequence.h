#ifndef _FrameSequence_
#define _FrameSequence_ 	
#include <vector>
#include <string>
namespace bnjcle001 
{	
	class FrameSequence
	{
		
		
		
		
		public: 
		
		int frameHeight =0;
		int frameWidth =0;
		
		std::vector<unsigned char **> imageSequence;
		
		FrameSequence(void);
		
		
		unsigned char** CreateFrame(int , int , int , int , char ** );
		
		~FrameSequence();
		
		void make_default_sequence(std::string filepath);
		void make_reverse_sequence(std::string filepath);
		void make_inverse_sequence(std::string filepath);
		void make_reinverse_sequence(std::string filepath);

		
		
		
		
			
	};
}
#endif
