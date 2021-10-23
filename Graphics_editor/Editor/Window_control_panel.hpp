#ifndef WINDOW_CONTROL_PANEL_VIDGET
#define WINDOW_CONTROL_PANEL_VIDGET

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Button_manager.hpp"

#include "Graphical_delegates.hpp"

class Window_control_panel : public Visual_object
{
private:

public:
	Window_control_panel(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *whose);
	~Window_control_panel();

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
};

#endif // WINDOW_CONTROL_PANEL_VIDGET