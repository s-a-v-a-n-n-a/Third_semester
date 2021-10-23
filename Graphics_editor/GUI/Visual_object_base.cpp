#include "Visual_object_base.hpp"

// const size_t VIDGETS_AMOUNT = 9;

Visual_object::Visual_object(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: objects(), type(par_type)
{
	stable_position = par_position;
	position = par_position;
	color    = par_color;

	width  = par_width;
	height = par_height;

	current_active = NULL;
	active         = false;
	visible        = true;
	reactive       = true;
	alive          = true;

	// for (size_t i = 0; i < VIDGETS_AMOUNT; ++i)
	// 	type_amount = 0;
}

void Visual_object::add_visual_object(Visual_object *par_object) 
{ 
	objects.add_to_end(par_object); 

	// type_amount[(size_t)par_object->get_type]++;
}

void Visual_object::slow_delete_visual_object(size_t index) 
{ /*delete (objects.get_array())[index];*/ 
	// Vidget_type deleting_type = objects.get_array()[index]->get_type();

	// что, если там лежал ноль
	// type_amount[deleting_type]--;

	objects.slow_delete(index); 
}

long long Visual_object::very_slow_delete_visual_object(Visual_object *par_object)
{
	// type_amount[par_object->get_type()]--;

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if(objects_array[i] == par_object)
		{
			objects.slow_delete(i);
			
			return i;
		}
	}

	return -1;
}

void Visual_object::set_position(const Radius_vector &par_position)
{
	Radius_vector offset = par_position - get_position();
	position = par_position;

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		objects_array[i]->set_position(objects_array[i]->get_position() + offset);
	}
}

void Visual_object::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_rectangle(position, get_color(), width, height);

	if (get_reactive())
	{
		Visual_object **objects_array = objects.get_array();
		size_t objects_amount = objects.get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			// printf("%d\n", objects_array[i]->get_visible());

			if (objects_array[i]->get_visible())
			{
				// if (current_active == objects_array[i])
				// {
				// 	Color current_color = objects_array[i]->get_color();
				// 	// current_color.set_a(MAX_COLOR_VALUE);

				// 	objects_array[i]->set_color(current_color);
				// }
				// else
				// {
				// 	Color current_color = objects_array[i]->get_color();
				// 	// current_color.set_a(MAX_COLOR_VALUE * 9 / 10);

				// 	objects_array[i]->set_color(current_color);
				// }
				objects_array[i]->draw(screen);
			}
		}
	}
}

bool Visual_object::point_inside(const size_t par_x, const size_t par_y)
{
	if (par_x >= position.get_x() && par_x <= position.get_x() + width &&
		par_y >= position.get_y() && par_y <= position.get_y() + height)
		return true;
	
	return false;
}

bool Visual_object::on_mouse(const Mouse_state state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		// set_active_state(true);
		size_t objects_amount = objects.get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse(state, par_x, par_y))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			{
				set_active(get_objects()->get_array()[i]);
				
				// slow_delete
				objects.extract(i);
				// push
				add_visual_object(get_active());
				
				return true;
			}
		}
	}

	return false;
}

bool Visual_object::on_key_pressed(const unsigned key_mask)
{
	// set_active_state(true);
	size_t objects_amount = objects.get_length();
	
	for (long long i = (long long)objects_amount - 1; i >= 0; --i)
	{
		if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_key_pressed(key_mask)) // ??????
		{
			set_active(get_objects()->get_array()[i]);
			
			// slow_delete
			objects.extract(i);
			// push
			add_visual_object(get_active());
			
			return true;
		}
	}

	return false;
}

void Visual_object::tick(Screen_information *screen, const double delta_time)
{
	assert(screen);

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		// printf("%d\n", objects_array[i]->get_visible());
		if (!objects_array[i]->get_alive())
		{
			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}

		objects_array[i]->tick(screen, delta_time);
	}
}