#ifndef GRAPHICAL_EDITOR_MAIN_PAGE
#define GRAPHICAL_EDITOR_MAIN_PAGE

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Button_manager.hpp"

#include "Vidget_types.hpp"

// #include "Editor_control_panel.hpp"
#include "Editor_delegates.hpp"
#include "Graphical_delegates.hpp"

// #include "Canvases_list.hpp"
#include "Canvas_manager_manager.hpp"
#include "Tools_vidget.hpp"
#include "Brush_size_manager.hpp"

#include "Pencil.hpp"

class Editor_control_panel;
class Palette;
class Canvas_manager_manager;

class Graphical_editor_main_page : public Visual_object
{
private:
	Pencil pencil;

public:
	Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, Texture *texture);
	~Graphical_editor_main_page();

	Color get_pencil_color() { return pencil.get_color(); }
	Pencil *get_pencil() { return &pencil; }

	void set_pencil_color(const Color &par_color) { pencil.set_color(par_color); }

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
	bool on_key_pressed(const unsigned key_state) override;
};


#endif // GRAPHICAL_EDITOR_MAIN_PAGE
