#ifndef GET_NEXT_LINE_SOLO_H
# define GET_NEXT_LINE_SOLO_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif 

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);

#endif
