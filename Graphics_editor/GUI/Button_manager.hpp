#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_delegate.hpp"
#include "../GUI/Button.hpp"

class Button_manager : public Visual_object
{
private:
	Vector_ll current_end_position;

public:
	Button_manager(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height);
	~Button_manager();

	Button *add_button(Button_delegate *par_delegate, const char *par_text, const Color par_color, const size_t par_width, const size_t par_height = DEFAULT_BUTTON_HEIGHT);
	Button *add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture);

	// void draw(Screen_information *screen) override;
};

#endif // BUTTON_MANAGER_H
