/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:04:55 by ehande            #+#    #+#             */
/*   Updated: 2021/04/16 13:46:45 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"
#include <unistd.h>
#include <stdio.h>

// char *mk_line(char ch)
// {
//     char *out;
    
//     out = malloc(sizeof(char) * 2);
//     out[1] = '\0';
//     out[0] = ch;
//     return(out);
// }

// void w(char **str)
// {
//     int i;
    
//     i = -1;
//     while(str && str[++i])
//         printf("%s\n", str[i]);
// }

// void check_2d()
// {
//     char **cmd;
    
//     cmd = malloc(sizeof(char *));
//     cmd[0] = NULL;
//     add_f_line(&cmd, mk_line('b'));
//     add_l_line(&cmd, mk_line('c'));
//     add_l_line(&cmd, mk_line('d'));
//     add_f_line(&cmd, mk_line('a'));
//     w(cmd);
//     printf("\n");
//     dl_l_line(&cmd);
//     dl_f_line(&cmd);
//     free_2d(&cmd);
//     w(cmd);
// }

int main()
{
    char *line;
    
    line = malloc(sizeof(char) * 1);
    line[0] = '\0';
    add_char_index(&line, 'a', 0);
    printf("%s\n", line);
    // buff[0] = 'a';
    // buff[1] = 'b';
    // buff[2] = 1;
    // printf("%s\n", buff);
    // line = NULL;
    // while(1)
    // {
    //     read(0, buff, 1);
    //     if (*buff == '\n')
    //     {
            
    //         printf("%s\n", line);
    //         del_at_index(&line, 0);
    //         printf("%s\n", line);
    //         free(line);
    //         line = NULL;
    //     }
    //     else
    //         make_line(&line, *buff);
    // }
    return(0);
}