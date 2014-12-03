
#include "includes.h"

CMenu::CMenu(CLauncherProgram *program, CScreen *previous) : CScreen(program, previous)
{
}

CMenu::~CMenu(void)
{
	for(vector<CMenuEntry *>::iterator i=menu_entries.begin(); i!=menu_entries.end(); i++)
		delete (*i);
}

void CMenu::AddEntry(CMenuEntry *entry)
{
	menu_entries.push_back(entry);
}




CListMenu::CListMenu(CLauncherProgram *program, CScreen *previous) : CMenu(program, previous)
{
	selected_entry = 0;
	scroll = 0;
}

CListMenu::~CListMenu(void)
{
}

void CListMenu::OnInputDirection(InputDirection dir)
{
	if(menu_entries.size() == 0)
		return;

	switch(dir)
	{
		case DOWN:
			selected_entry++;
			break;
		case UP:
			selected_entry--;
			break;
		default:
			break;
	}

	/*while(selected_entry < 0)
		selected_entry += (int)menu_entries.size();
	selected_entry %= (int)menu_entries.size();*/

	selected_entry = min((int)menu_entries.size()-1, max(0, selected_entry));

	if(selected_entry < scroll + 1)
		scroll = max(selected_entry - 1, 0);
	if(selected_entry > scroll + (GetProgram()->GetTheme()->GetMaxListMenuEntries() - 1))
		scroll = selected_entry - (GetProgram()->GetTheme()->GetMaxListMenuEntries() - 1);
}


void CListMenu::Render(SDL_Renderer *renderer)
{
	CTheme *theme = GetProgram()->GetTheme();
	CRect menu_rect = theme->GetMenuRect();

	int x, y;

	x = menu_rect.x;
	y = menu_rect.y;

	CMenuEntry *entry;
	for(int i=scroll; i<(int)menu_entries.size(); i++)
	{
		if(i-scroll > theme->GetMaxListMenuEntries())
			break;

		entry = menu_entries[i];

		SDL_Texture *tex;
		if(i==selected_entry)
			tex = entry->GetSelectedTexture();
		else
			tex = entry->GetUnselectedTexture();

		int width, height;
		SDL_QueryTexture(tex, 0, 0, &width, &height);
		SDL_Rect dst_rect = { x, y, width, height };
		SDL_RenderCopy(renderer, tex, 0, &dst_rect);

		y += theme->GetListMenuEntryDistance();
	}
}

void CListMenu::OnInputFire(void)
{
	if(menu_entries.size() > 0)
		menu_entries[selected_entry]->Trigger();
}
