#ifndef GRAPHICSYSTEM_HPP
#define GRAPHICSYSTEM_HPP

class GraphicSystem
{
public:
	const static void	*_mlx;
	GraphicSystem(void);
	virtual ~GraphicSystem(void);
	static void	*getMlx(void);
};

#endif /* GRAPHICSYSTEM_HPP */
