

#include "Thomas/Renderer/Shader.h"


/*  _________________________________________________________________________ */
struct Render {
    static void init();
    static void update();
    static void draw();
    static void cleanup();
	static void Add_Obj();
	static GLuint Gen_Text(const char* txt_file);
	static void temp_physics();
	static bool simple_collision(glm::vec2 minA, glm::vec2 maxA, glm::vec2 minB, glm::vec2 maxB);

	inline static int obj_shape{};
	inline static int sel{};					// Selected object
	inline static float aspect_ratio;
		// Aspect ratio of the screen

	struct Object {
		GLenum			primitive_type;
		Shader		shdr_pgm;
		GLuint				vbo_hdl;
		GLuint				vaoid{};
		GLuint				idx_elem_cnt{};
		int					shape{};
		glm::vec2			scaling{};
		glm::vec2			translation{};
		float					rotation{};
		glm::mat3		world_to_ndc_xform{};	// For Camera
		glm::mat3		mdl_to_ndc_xform{};
		
		//Square 
		glm::vec2			min{};
		glm::vec2			max{};

		//Circle
		glm::vec2			center{};
		float radius;

		//Texture
		GLuint texid;
		GLsizei pixel_cnt, byte_cnt;
		int text_file{};
		int animation_but{};
		int counter{};
		int switch_text{};

		//Bounding Box
		int BBtog{};
		int collision_detected{};
		GLuint Bvaoid;
		int reset_but{};

		void setup_vao();
		void setup_shdrpgm();
		void draw();
		void draw_collider();
		void Camera2D_Init();
		void minmax();
		void animation(int slices);
	};

	struct Color {
		float r{};
		float g{};
		float b{};
	};

	// Multiple model
	static std::vector<Object> mdl_obj;
	static std::vector<Object> collider_obj;
	

	
	
};

