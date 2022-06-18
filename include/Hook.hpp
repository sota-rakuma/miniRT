#ifndef HOOK_H
#define HOOK_H


struct Hook
{
	static int	close(void *param);
	//for test
	static int close(int keycode, void *param);
};


#endif /* HOOK_H */
