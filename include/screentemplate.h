

#ifndef _SCREENTEMPLATE_H
#define _SCREENTEMPLATE_H


class CScreenTemplate
{
	public:
		virtual ~CScreenTemplate(void) {}

		virtual CScreen *CreateScreen(void) =0;
};


#endif
