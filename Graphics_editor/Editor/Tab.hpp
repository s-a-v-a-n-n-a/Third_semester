#ifndef TAB_VIDGET
#define TAB_VIDGET

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

class Tab;

#include "Graphical_delegates.hpp"
#include "Editor_delegates.hpp"

const size_t DEFAULT_TAB_WIDTH = 250;
const size_t DEFAULT_TAB_HEIGHT = 80;

class Tab : public Visual_object
{
private:
	Visual_object *parent;

public:
	Tab(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *par_parent);
	Tab(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Visual_object *par_parent);
	~Tab() = default;

	// void draw(Screen_information *screen) override;
};

#endif // TAB_VIDGET
