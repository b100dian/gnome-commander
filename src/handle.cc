/*
    GNOME Commander - A GNOME based file manager
    Copyright (C) 2001-2006 Marcus Bjurman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <config.h>
#include <glib.h>
#include "handle.h"

using namespace std;


Handle  *handle_new (gpointer ref)
{
    Handle *h = g_new (Handle, 1);

    h->ref_count = 1;
    h->ref = ref;

    return h;
}


void handle_free (Handle *h)
{
    g_return_if_fail (h);
    g_return_if_fail (h->ref_count > 0);

    g_free (h);
}


void handle_ref (Handle *h)
{
    g_return_if_fail (h);

    h->ref_count++;
}


void handle_unref (Handle *h)
{
    g_return_if_fail (h);
    g_return_if_fail (h->ref_count > 0);

    h->ref_count--;
}


gpointer handle_get_ref (Handle *h)
{
    g_return_val_if_fail (h, NULL);

    return h->ref;
}



