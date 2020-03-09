/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:55:25 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/09 12:26:10 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DEFINE_H
# define ERROR_DEFINE_H

# define USAGE "usage: Cub3D file [--save]\n"

# define CUB_FILE "Bad file, must end with '.cub'"
# define XPM_FILE "Bad texture file, must be '.xpm'"

# define OPEN_FILE "Couldn't open file."

# define INVALID_DES "Invalid description element."
# define NB_RES "Wrong number of arguments in map resolution. Two needed."
# define ARG_RES "Invalid argument(s) in map resolution."
# define VAL_RES "Wrong value argument in map resolution. Minimum is 50x50."
# define NB_COLOR "Wrong number of arguments in color definition. One needed."
# define ARG_COLOR "Invalid argument(s) in color definition."
# define VAL_COLOR "Wrong value of color argument. Colors go from 0 to 255."
# define NB_TEX "Wrong number of argument in texture description."
# define OPEN_TEX_FILE "Couldn't open texture file."

#endif
