#ifndef CORE_H
# define CORE_H

typedef struct s_mini	t_mini;
typedef struct s_gc		t_gc;

extern t_mini			g_minishell;

t_gc					*get_gc(void);

#endif
