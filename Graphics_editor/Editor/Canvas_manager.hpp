#ifndef CANVAS_MANAGER_SINGLE
#define CANVAS_MANAGER_SINGLE

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Pencil.hpp"
#include "Canvas.hpp"
#include "Tab.hpp"

class Canvas_manager : public Visual_object
{
private:
	Tab *tab;

public:
	// поэтому получает информацию о главном
	Canvas_manager(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil, const Radius_vector &offset, const size_t predecessors_amount);
	~Canvas_manager();

	void draw(Screen_information *screen) override;

	void set_offset(const Radius_vector &par_offset);
	Radius_vector get_offset() const;
};

#endif // CANVAS_MANAGER_SINGLE