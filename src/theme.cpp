
#include "includes.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 rmask = 0xff000000;
    const Uint32 gmask = 0x00ff0000;
    const Uint32 bmask = 0x0000ff00;
    const Uint32 amask = 0x000000ff;
#else
    const Uint32 rmask = 0x000000ff;
    const Uint32 gmask = 0x0000ff00;
    const Uint32 bmask = 0x00ff0000;
    const Uint32 amask = 0xff000000;
#endif


CTheme::CTheme(CLauncherProgram *program)
{
	this->program = program;
	Load();
}

CTheme::~CTheme(void)
{
	UnLoad();
}

void CTheme::Load(void)
{
	loaded_completely = true;


	// make changes here, if you want to change specific positions on the screen or filenames

	screen_width = SCREEN_WIDTH;
	screen_height = SCREEN_HEIGHT;

	arrow_down_x = screen_width - 30;	arrow_down_y = screen_height - 120;
	arrow_up_x = arrow_down_x;			arrow_up_y = 50;

	menu_rect = CRect(75, 75, screen_width - 75*2, 682 - 75);
	list_menu_entry_distance = 38;
	unselected_menu_text_color = CreateColor(255, 255, 255);
	selected_menu_text_color = CreateColor(0, 0, 0);
	selected_menu_entry_text_background_color = CreateColor(255, 255, 255);

	thumb_width = 160;
	thumb_height = 110;
	thumbs_menu_entry_width = thumb_width;
	thumbs_menu_entry_height = thumb_height + 25;

	thumbs_menu_entry_distance_x = (menu_rect.width - thumbs_menu_entry_width * GetMaxThumbsMenuEntriesX()) / (GetMaxThumbsMenuEntriesX() - 1);
	thumbs_menu_entry_distance_y = (menu_rect.height - thumbs_menu_entry_height * GetMaxThumbsMenuEntriesY()) / (GetMaxThumbsMenuEntriesY() - 1);


	string theme_folder = string(THEME_FOLDER) + string("/");

	background = LoadTexture(theme_folder + string("background.png"));
	list_menu_entry_font = LoadFont(theme_folder + string("font.ttf"), 25);
	thumbs_menu_entry_font = LoadFont(theme_folder + string("font.ttf"), 16);

	arrow_down = LoadTexture(theme_folder + string("arrow_down.png"));
	arrow_up = LoadTexture(theme_folder + string("arrow_up.png"));

	thumbnail_border = LoadBorder(thumb_width, thumb_height,	theme_folder + string("border_unselected/left.png"),
																theme_folder + string("border_unselected/right.png"),
																theme_folder + string("border_unselected/top.png"),
																theme_folder + string("border_unselected/bottom.png"),
																theme_folder + string("border_unselected/left_top.png"),
																theme_folder + string("border_unselected/right_top.png"),
																theme_folder + string("border_unselected/left_bottom.png"),
																theme_folder + string("border_unselected/right_bottom.png"));
	thumbnail_border_selected = LoadBorder(thumb_width, thumb_height,	theme_folder + string("border_selected/left.png"),
																theme_folder + string("border_selected/right.png"),
																theme_folder + string("border_selected/top.png"),
																theme_folder + string("border_selected/bottom.png"),
																theme_folder + string("border_selected/left_top.png"),
																theme_folder + string("border_selected/right_top.png"),
																theme_folder + string("border_selected/left_bottom.png"),
																theme_folder + string("border_selected/right_bottom.png"));
}



void CTheme::UnLoad(void)
{
	UnLoadTexture(background);
	UnLoadTexture(arrow_up);
	UnLoadTexture(arrow_down);
	UnLoadSurface(thumbnail_border);
	UnLoadSurface(thumbnail_border_selected);
	UnLoadFont(list_menu_entry_font);
	UnLoadFont(thumbs_menu_entry_font);
}

SDL_Surface *CTheme::LoadSurface(string file)
{
	SDL_Surface *s = IMG_Load(file.c_str());
	if(!s)
		loaded_completely = false;
	return s;
}

SDL_Texture *CTheme::LoadTexture(string file)
{
	SDL_Texture *texture = program->LoadTexture(file.c_str());

	if(!texture)
		loaded_completely = false;

	return texture;
}

TTF_Font *CTheme::LoadFont(string file, int size)
{
	TTF_Font *font = TTF_OpenFont(file.c_str(), size);
	if(!font)
		loaded_completely = false;
	return font;
}

SDL_Surface *CTheme::LoadBorder(int width, int height, string left, string right, string top, string bottom, string left_top, string right_top, string left_bottom, string right_bottom)
{
	SDL_Surface *left_surface, *right_surface, *top_surface, *bottom_surface, *left_top_surface, *right_top_surface, *left_bottom_surface, *right_bottom_surface;

	left_surface = LoadSurface(left);
	right_surface = LoadSurface(right);
	top_surface = LoadSurface(top);
	bottom_surface = LoadSurface(bottom);
	left_top_surface = LoadSurface(left_top);
	right_top_surface = LoadSurface(right_top);
	left_bottom_surface = LoadSurface(left_bottom);
	right_bottom_surface = LoadSurface(right_bottom);

	if(!left_surface || !right_surface || !top_surface || !bottom_surface || !left_top_surface || !right_top_surface || !left_bottom_surface || !right_bottom_surface)
	{
		loaded_completely = false; // actually not necessary, because LoadSurface also does this

		SDL_FreeSurface(left_surface);
		SDL_FreeSurface(right_surface);
		SDL_FreeSurface(top_surface);
		SDL_FreeSurface(bottom_surface);
		SDL_FreeSurface(left_top_surface);
		SDL_FreeSurface(right_top_surface);
		SDL_FreeSurface(left_bottom_surface);
		SDL_FreeSurface(right_bottom_surface);

		return 0;
	}

	SDL_SetSurfaceBlendMode(left_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(right_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(top_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(bottom_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(left_top_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(right_top_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(left_bottom_surface, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(right_bottom_surface, SDL_BLENDMODE_NONE);


	SDL_Surface *border = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(border, 0, SDL_MapRGBA(border->format, 0, 0, 0, 0));

	SDL_Rect src, dst;
	int tile_count;
	int dist;
	int i;

	// top
	dist = width - (left_top_surface->w + right_top_surface->w);
	tile_count = (int)ceil((float)dist / (float)top_surface->w);
	src.x = 0;
	src.y = 0;
	src.w = top_surface->w;
	src.h = top_surface->h;
	dst.y = 0;
	for(i=0; i<tile_count; i++)
	{
		dst.x = left_top_surface->w + i * top_surface->w;
		if(i == tile_count-1)
			src.w = dist - i * top_surface->w;
		SDL_BlitSurface(top_surface, &src, border, &dst);
	}

	// bottom
	dist = width - (left_bottom_surface->w + right_bottom_surface->w);
	tile_count = (int)ceil((float)dist / (float)bottom_surface->w);
	src.x = 0;
	src.y = 0;
	src.w = bottom_surface->w;
	src.h = bottom_surface->h;
	dst.y = height - bottom_surface->h;
	for(i=0; i<tile_count; i++)
	{
		dst.x = left_bottom_surface->w + i * bottom_surface->w;
		if(i == tile_count-1)
			src.w = dist - i * bottom_surface->w;
		SDL_BlitSurface(bottom_surface, &src, border, &dst);
	}

	// left
	dist = height - (left_top_surface->h + left_bottom_surface->h);
	tile_count = (int)ceil((float)dist / (float)left_surface->h);
	src.x = 0;
	src.y = 0;
	src.w = left_surface->w;
	src.h = left_surface->h;
	dst.x = 0;
	for(i=0; i<tile_count; i++)
	{
		dst.y = left_top_surface->h + i * left_surface->h;
		if(i == tile_count-1)
			src.h = dist - i * left_surface->h;
		SDL_BlitSurface(left_surface, &src, border, &dst);
	}

	// right
	dist = height - (right_top_surface->h + right_bottom_surface->h);
	tile_count = (int)ceil((float)dist / (float)right_surface->h);
	src.x = 0;
	src.y = 0;
	src.w = right_surface->w;
	src.h = right_surface->h;
	dst.x = width - right_surface->w;
	for(i=0; i<tile_count; i++)
	{
		dst.y = right_top_surface->h + i * right_surface->h;
		if(i == tile_count-1)
			src.h = dist - i * right_surface->h;
		SDL_BlitSurface(right_surface, &src, border, &dst);
	}

	// left top
	dst.x = 0;
	dst.y = 0;
	dst.w = left_top_surface->w;
	dst.w = left_top_surface->h;
	SDL_BlitSurface(left_top_surface, 0, border, &dst);

	// right top
	dst.x = width - right_top_surface->w;
	dst.y = 0;
	dst.w = right_top_surface->w;
	dst.w = right_top_surface->h;
	SDL_BlitSurface(right_top_surface, 0, border, &dst);

	// left bottom
	dst.x = 0;
	dst.y = height - left_bottom_surface->h;
	dst.w = left_bottom_surface->w;
	dst.w = left_bottom_surface->h;
	SDL_BlitSurface(left_bottom_surface, 0, border, &dst);

	// right bottom
	dst.x = width - right_bottom_surface->w;
	dst.y = height - right_bottom_surface->h;
	dst.w = right_bottom_surface->w;
	dst.w = right_bottom_surface->h;
	SDL_BlitSurface(right_bottom_surface, 0, border, &dst);



	SDL_FreeSurface(left_surface);
	SDL_FreeSurface(right_surface);
	SDL_FreeSurface(top_surface);
	SDL_FreeSurface(bottom_surface);
	SDL_FreeSurface(left_top_surface);
	SDL_FreeSurface(right_top_surface);
	SDL_FreeSurface(left_bottom_surface);
	SDL_FreeSurface(right_bottom_surface);

	return border;
}


void CTheme::UnLoadTexture(SDL_Texture *tex)
{
	if(!tex)
		return;
	SDL_DestroyTexture(tex);
}

void CTheme::UnLoadSurface(SDL_Surface *surface)
{
	if(!surface)
		return;
	SDL_FreeSurface(surface);
}

void CTheme::UnLoadFont(TTF_Font *font)
{
	if(!font)
		return;
	TTF_CloseFont(font);
}


SDL_Texture *CTheme::RenderUnselectedListMenuEntry(string text)
{
	SDL_Surface *surface = TTF_RenderText_Solid(GetListMenuEntryFont(), text.c_str(), GetUnselectedMenuEntryTextColor());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture *CTheme::RenderSelectedListMenuEntry(string text)
{
	SDL_Surface *surface = RenderTextWithBackground(GetListMenuEntryFont(), text, GetSelectedMenuEntryTextColor(), GetSelectedMenuEntryTextBackgroundColor());

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Surface *CTheme::RenderBasicThumbsMenuEntry(SDL_Surface *thumb, bool selected)
{
	SDL_Surface *surface = SDL_CreateRGBSurface(0, thumbs_menu_entry_width, thumbs_menu_entry_height, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	SDL_Rect dst, src;

	dst.x = (thumbs_menu_entry_width - thumb_width) / 2;
	dst.y = 0;
	dst.w = thumb_width;
	dst.h = thumb_height;

	if(thumb)
	{
		float dst_aspect = (float)thumb_height / (float)thumb_width;

		if(dst_aspect > (float)thumb->h / (float)thumb->w) // thumbnail is wider
		{
			src.y = 0;
			src.h = thumb->h;

			int w = thumb->h / (dst_aspect);
			src.x = (thumb->w - w) / 2;
			src.w = w;
		}
		else // thumbnail is taller
		{
			src.x = 0;
			src.w = thumb->w;

			int h = thumb->w * dst_aspect;
			src.y = (thumb->h - h) / 2;
			src.h = h;
		}

		SDL_BlitScaled(thumb, &src, surface, &dst);
	}
	else
		SDL_FillRect(surface, &dst, 0xff0000ff);

	SDL_BlitSurface(selected ? GetThumbnailBorderSelected() : GetThumbnailBorder(), 0, surface, 0);

	return surface;
}

SDL_Texture *CTheme::RenderUnselectedThumbsMenuEntry(string text, SDL_Surface *thumb)
{
	SDL_Surface *surface = RenderBasicThumbsMenuEntry(thumb, false);

	SDL_Surface *text_surface = TTF_RenderText_Solid(GetThumbsMenuEntryFont(), text.c_str(), GetUnselectedMenuEntryTextColor());
	SDL_Rect r;
	r.x = surface->w / 2 - text_surface->w / 2;
	r.y = surface->h - text_surface->h;

	SDL_BlitSurface(text_surface, 0, surface, &r);
	SDL_FreeSurface(text_surface);

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Texture *CTheme::RenderSelectedThumbsMenuEntry(string text, SDL_Surface *thumb)
{
	SDL_Surface *surface = RenderBasicThumbsMenuEntry(thumb, true);

	SDL_Surface *text_surface = RenderTextWithBackground(GetThumbsMenuEntryFont(), text.c_str(), GetSelectedMenuEntryTextColor(), GetSelectedMenuEntryTextBackgroundColor());
	SDL_Rect r;
	r.x = surface->w / 2 - text_surface->w / 2;
	r.y = surface->h - text_surface->h;

	SDL_BlitSurface(text_surface, 0, surface, &r);
	SDL_FreeSurface(text_surface);

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Color CTheme::CreateColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

SDL_Surface *CTheme::RenderTextWithBackground(TTF_Font *font, string text, SDL_Color fg, SDL_Color bg)
{
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), fg);

	SDL_Surface *surface = SDL_CreateRGBSurface(0, text_surface->w, text_surface->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, bg.r, bg.g, bg.b, bg.a));
	SDL_BlitSurface(text_surface, 0, surface, 0);
	SDL_FreeSurface(text_surface);

	return surface;
}






