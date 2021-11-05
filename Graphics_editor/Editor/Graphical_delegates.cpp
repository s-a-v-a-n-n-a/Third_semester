#include "Graphical_delegates.hpp"

// Interactive
// ---------------------------------------------------------------------------------------------------------
Interactive::Interactive(Visual_object *par_to_interact) 
: to_interact(nullptr)
{
	to_interact = par_to_interact;
}

bool Interactive::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	Color changing_color = to_interact->get_color();
	int new_a = (int)MAX_COLOR_VALUE;
	
	if (to_interact->point_inside(to.get_x(), to.get_y()))
	{
		changing_color.set_a(new_a * 3 / 4);
	}
	else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
	{
		changing_color.set_a(new_a);
	}

	to_interact->set_color(changing_color);

	return true;
}

void Interactive::set_interactive(Visual_object *par_to_interact)
{
	to_interact = par_to_interact;
}
// ---------------------------------------------------------------------------------------------------------

// Animating
// ---------------------------------------------------------------------------------------------------------
Animating::Animating(Visual_object *par_to_animate) 
: to_animate(nullptr), move_in(nullptr), move_out(nullptr), move_in_index(-1), move_out_index(-1)
{
	to_animate = par_to_animate;
}

bool Animating::on_mouse_click(const size_t par_x, const size_t par_y)
{
	if (move_in)
	{
		Animation_manager::get_instance()->slow_delete_animation(move_in);
		move_in = nullptr;
		move_in_index = -1;
	}

	if (move_out)
	{
		Animation_manager::get_instance()->slow_delete_animation(move_out);
		move_out = nullptr;
		move_out_index = -1;
	}

	return true;
}

bool Animating::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (to_animate->point_inside(to.get_x(), to.get_y()))
	{
		if (!move_in)
		{
			if (move_out)
			{
				Animation_manager::get_instance()->slow_delete_animation(move_out);
				move_out = nullptr;
				move_out_index = -1;
			}

			move_in = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), 0.01);
			move_in_index = Animation_manager::get_instance()->add_animation(move_in);
		}
	}
	else if(!to_animate->point_inside(to.get_x(), to.get_y()))
	{
		if (!move_out)
		{
			if (move_in)
			{
				Animation_manager::get_instance()->slow_delete_animation(move_in);
				move_in = nullptr;
				move_in_index = -1;
			}
			
			move_out = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), 0.01);
			move_out_index = Animation_manager::get_instance()->add_animation(move_out);
		}
	}

	return true;
}

void Animating::set_animating(Visual_object *par_to_animate)
{
	to_animate = par_to_animate;
}
// ---------------------------------------------------------------------------------------------------------

// Restore_delegate
// ---------------------------------------------------------------------------------------------------------
Restore_delegate::Restore_delegate(Visual_object *par_to_restore)
: to_restore(nullptr)
{
	to_restore = par_to_restore;
}

bool Restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_restore->set_visible(true);
	to_restore->set_reactive(true);

	return true;
}
// ---------------------------------------------------------------------------------------------------------

// Animating_restore_delegate
// ---------------------------------------------------------------------------------------------------------
Animating_restore_delegate::Animating_restore_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact)
: Restore_delegate(par_to_restore), Animating(par_to_interact)
{
	;
}

bool Animating_restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Restore_delegate::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_restore_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}
// ---------------------------------------------------------------------------------------------------------


// Restore_interactive_delegate
// ---------------------------------------------------------------------------------------------------------
Restore_interactive_delegate::Restore_interactive_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact) 
: Restore_delegate(par_to_restore), Interactive(par_to_interact)
{
	;
}

bool Restore_interactive_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Interactive::on_mouse_move(from, to);
}
// ---------------------------------------------------------------------------------------------------------


// Roll_up_delegate
// ---------------------------------------------------------------------------------------------------------
Roll_up_delegate::Roll_up_delegate(Visual_object *par_to_roll_up)
: to_roll_up(nullptr)
{
	to_roll_up = par_to_roll_up;
}

bool Roll_up_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_roll_up->set_visible(false);
	to_roll_up->set_reactive(false);

	return true;
}

Visual_object *Roll_up_delegate::get_roll_up() { return to_roll_up; }
// ---------------------------------------------------------------------------------------------------------

// Animating_roll_up_delegate
// ---------------------------------------------------------------------------------------------------------
Animating_roll_up_delegate::Animating_roll_up_delegate(Visual_object *par_to_roll_up, Visual_object *par_to_interact)
: Roll_up_delegate(par_to_roll_up), Animating(par_to_interact)
{
	;
}

bool Animating_roll_up_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Roll_up_delegate::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_roll_up_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}
// ---------------------------------------------------------------------------------------------------------

// Close_delegate
// ---------------------------------------------------------------------------------------------------------
Close_delegate::Close_delegate(Visual_object *par_to_close)
: to_close(nullptr)
{
	to_close = par_to_close;
}

bool Close_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_close->set_alive(false);

	return false;
}
// ---------------------------------------------------------------------------------------------------------


// Close_interactive_delegate 
// ---------------------------------------------------------------------------------------------------------
Close_interactive_delegate::Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact) 
: Close_delegate(par_to_close), to_interact(nullptr)
{
	to_interact = par_to_interact;
}

bool Close_interactive_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	Color changing_color = to_interact->get_color();
	int new_a = (int)MAX_COLOR_VALUE;
	
	if (to_interact->point_inside(to.get_x(), to.get_y()))
	{
		changing_color.set_a(new_a * 3 / 4);
	}
	else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
	{
		changing_color.set_a(new_a);
	}

	to_interact->set_color(changing_color);

	return true;
}
// ---------------------------------------------------------------------------------------------------------

// Change_color 
// ---------------------------------------------------------------------------------------------------------
Change_color::Change_color(Pencil *par_pencil, const Color &par_color)
: pencil(nullptr), color(WHITE)
{
	pencil = par_pencil;
	color = par_color;
}

bool Change_color::on_mouse_click(const size_t par_x, const size_t par_y)
{
	pencil->set_color(color);

	return true;
}
// ---------------------------------------------------------------------------------------------------------

// Change_thickness
// ---------------------------------------------------------------------------------------------------------
Change_thickness::Change_thickness(Pencil *par_pencil, const size_t par_size)
: pencil(nullptr), size(0)
{
	pencil = par_pencil;
	size = par_size;
}

bool Change_thickness::on_mouse_click(const size_t par_x, const size_t par_y)
{
	pencil->set_size(size);

	return true;
}
// ---------------------------------------------------------------------------------------------------------

// Drag_and_drop_delegate
// ---------------------------------------------------------------------------------------------------------
Drag_and_drop_delegate::Drag_and_drop_delegate(Visual_object *par_to_change_place) 
: to_change_place(nullptr), clicked(false), first_position(0, 0), last_position(0, 0)
{
	to_change_place = par_to_change_place;
}

bool Drag_and_drop_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	clicked = true;

	first_position = Vector_ll(par_x, par_y);

	// to_change_place->set_reactive(false);

	return true;
}

bool Drag_and_drop_delegate::on_mouse_release()
{
	clicked = false;

	first_position = last_position;

	// to_change_place->set_reactive(true);

	return true;
}

bool Drag_and_drop_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (clicked)
	{
		last_position = to;

		Vector_ll new_position = to_change_place->get_position() + last_position - first_position;
		bool bad_position = false;

		if (new_position.get_x() < 0)
		{
			new_position.set_x(0);
			bad_position = true;
		}
		if (new_position.get_y() < 0)
		{
			new_position.set_y(0);
			bad_position = true;
		}

		if (bad_position)
			on_mouse_release();

		to_change_place->set_position(new_position);
		first_position = last_position;
	}

	return true;
}
// ---------------------------------------------------------------------------------------------------------