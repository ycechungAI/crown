/*
Copyright (c) 2013 Daniele Bartolini, Michele Rossi
Copyright (c) 2012 Daniele Bartolini, Simone Boscaratto

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Gui.h"
#include "LuaEnvironment.h"
#include "LuaStack.h"
#include "Vector3.h"
#include "Color4.h"

namespace crown
{

//-----------------------------------------------------------------------------
CE_EXPORT int gui_move(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);

	const Vector3 pos = stack.get_vector3(2);

	gui->move(pos);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_create_rect(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	const Vector3 pos = stack.get_vector3(2);
	const Vector2 size = stack.get_vector2(3);
	// TMP FIXME FIXME FIXME
	const Color4 color(1.0f, 1.0f, 1.0f, 1.0f);

	GuiComponentId rect_id = gui->create_rect(pos, size, color);
	stack.push_gui_component_id(rect_id);

	return 1;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_update_rect(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId rect_id = stack.get_gui_component_id(2);
	const Vector3 pos = stack.get_vector3(3);
	const Vector2 size = stack.get_vector2(4);
	// TMP FIXME FIXME FIXME
	const Color4 color(1.0f, 1.0f, 1.0f, 1.0f);

	gui->update_rect(rect_id, pos, size, color);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_destroy_rect(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId rect_id = stack.get_gui_component_id(2);

	gui->destroy_rect(rect_id);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_create_triangle(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	const Vector2 p1 = stack.get_vector2(2);
	const Vector2 p2 = stack.get_vector2(3);
	const Vector2 p3 = stack.get_vector2(3);
	// TMP FIXME FIXME FIXME
	const Color4 color(1.0f, 1.0f, 1.0f, 1.0f);

	GuiComponentId triangle_id = gui->create_triangle(p1, p2, p3, color);

	stack.push_gui_component_id(triangle_id);

	return 1;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_update_triangle(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId triangle_id = stack.get_gui_component_id(2);
	const Vector2 p1 = stack.get_vector2(3);
	const Vector2 p2 = stack.get_vector2(4);
	const Vector2 p3 = stack.get_vector2(5);
	// TMP FIXME FIXME FIXME
	const Color4 color(1.0f, 1.0f, 1.0f, 1.0f);

	gui->update_triangle(triangle_id, p1, p2, p3, color);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_destroy_triangle(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId triangle_id = stack.get_gui_component_id(2);

	gui->destroy_triangle(triangle_id);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_create_image(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	const char* mat_name = stack.get_string(2);
	const Vector3 pos = stack.get_vector3(3);
	const Vector2 size = stack.get_vector2(4);

	ResourceId mat_id;
	mat_id.id = hash::murmur2_64(mat_name, string::strlen(mat_name), 0);

	GuiImageId image_id = gui->create_image(mat_id, pos, size);

	stack.push_gui_component_id(image_id);

	return 1;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_update_image(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId image_id = stack.get_gui_component_id(2);
	const Vector3 pos = stack.get_vector3(3);
	const Vector2 size = stack.get_vector2(4);

	gui->update_image(image_id, pos, size);

	return 0;
}

//-------------------------------------------------------------------------
CE_EXPORT int gui_destroy_image(lua_State* L)
{
	LuaStack stack(L);

	Gui* gui = stack.get_gui(1);
	GuiComponentId image_id = stack.get_gui_component_id(2);

	gui->destroy_image(image_id);

	return 0;
}

//-----------------------------------------------------------------------------
void load_gui(LuaEnvironment& env)
{
	env.load_module_function("Gui", "move",				gui_move);
	env.load_module_function("Gui", "create_rect",		gui_create_rect);
	env.load_module_function("Gui", "update_rect",		gui_update_rect);
	env.load_module_function("Gui", "destroy_rect",		gui_destroy_rect);
	env.load_module_function("Gui", "create_triangle",	gui_create_triangle);
	env.load_module_function("Gui", "update_triangle",	gui_update_triangle);
	env.load_module_function("Gui", "destroy_triangle",	gui_destroy_triangle);
	env.load_module_function("Gui", "create_image",		gui_create_image);
	env.load_module_function("Gui", "update_image",		gui_update_image);
	env.load_module_function("Gui", "destroy_image",	gui_destroy_image);
}


} // namespace crown