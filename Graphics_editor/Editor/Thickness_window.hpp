#ifndef THICKNESS_WINDOW_H
#define THICKNESS_WINDOW_H

#include "../GUI/Slider.hpp"

#include "Graphical_delegates.hpp"
#include "Pencil.hpp"
#include "Window.hpp"

const size_t INDENT_SIZE = 10;

class Thickness_window : public Window 
{
public:
	Thickness_window(const Visual_object::Config &par_base, Pencil *pencil)
	: Window(par_base)
	{
		Change_thickness_non_fixedly *delegate = new Change_thickness_non_fixedly(pencil, DEFAULT_PENCIL_SIZE);
		Slider *slider = create_slider(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, delegate);
	}

	Slider *create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate)
	{
		Slider *slider = new Slider({(size_t)Vidget_type::SLIDER, position, NULL, TRANSPARENT, width, height}, par_delegate, 0, 100, true); // умные мысли преследовали её, но она была быстрее

		add_visual_object(slider);
		return slider;
	}
};

#endif // THICKNESS_WINDOW_H
