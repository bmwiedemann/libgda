/* dummy-object.h
 *
 * Copyright (C) 2009 Vivien Malerba
 *
 * This Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef __DUMMY_OBJECT_H_
#define __DUMMY_OBJECT_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define DUMMY_TYPE_OBJECT          (dummy_object_get_type())
#define DUMMY_OBJECT(obj)          G_TYPE_CHECK_INSTANCE_CAST (obj, dummy_object_get_type(), DummyObject)
#define DUMMY_OBJECT_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST (klass, dummy_object_get_type (), DummyObjectClass)
#define DUMMY_IS_OBJECT(obj)       G_TYPE_CHECK_INSTANCE_TYPE (obj, dummy_object_get_type ())

typedef struct _DummyObject DummyObject;
typedef struct _DummyObjectClass DummyObjectClass;

/* struct for the object's data */
struct _DummyObject
{
	GObject                 object;
};


/* struct for the object's class */
struct _DummyObjectClass
{
	GObjectClass               parent_class;
	void                     (*sig0)   (DummyObject *object);
	void                     (*sig1)   (DummyObject *object, gint i);
	void                     (*sig2)   (DummyObject *object, gint i, gchar *str);
};

GType               dummy_object_get_type                (void) G_GNUC_CONST;
DummyObject        *dummy_object_new                     (void);

G_END_DECLS

#endif