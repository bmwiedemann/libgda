/*
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

#include <string.h>
#include <glib/gi18n-lib.h>
#include "browser-variable.h"

/* 
 * Main static functions 
 */
static void browser_variable_class_init (BrowserVariableClass *klass);
static void browser_variable_init (BrowserVariable *bvar);
static void browser_variable_dispose (GObject *object);

/* get a pointer to the parents to be able to call their destructor */
static GObjectClass  *parent_class = NULL;

struct _BrowserVariablePrivate {
	GdaHolder *holder;
};

GType
browser_variable_get_type (void)
{
	static GType type = 0;

	if (G_UNLIKELY (type == 0)) {
		static GStaticMutex registering = G_STATIC_MUTEX_INIT;
		static const GTypeInfo info = {
			sizeof (BrowserVariableClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) browser_variable_class_init,
			NULL,
			NULL,
			sizeof (BrowserVariable),
			0,
			(GInstanceInitFunc) browser_variable_init
		};

		
		g_static_mutex_lock (&registering);
		if (type == 0)
			type = g_type_register_static (G_TYPE_OBJECT, "BrowserVariable", &info, 0);
		g_static_mutex_unlock (&registering);
	}
	return type;
}

static void
browser_variable_class_init (BrowserVariableClass *klass)
{
	GObjectClass   *object_class = G_OBJECT_CLASS (klass);
	parent_class = g_type_class_peek_parent (klass);

	object_class->dispose = browser_variable_dispose;
}

static void
browser_variable_init (BrowserVariable *bvar)
{
	bvar->priv = g_new0 (BrowserVariablePrivate, 1);
	bvar->priv->holder = NULL;
}

/**
 * browser_variable_new
 *
 * Creates a new #BrowserVariable object
 *
 * Returns: the new object
 */
BrowserVariable*
browser_variable_new (GdaHolder *holder)
{
	BrowserVariable *bvar;

	g_return_val_if_fail (GDA_IS_HOLDER (holder), NULL);

	bvar = BROWSER_VARIABLE (g_object_new (BROWSER_TYPE_VARIABLE, NULL));
	bvar->priv->holder = g_object_ref (holder);

	return bvar;
}

static void
browser_variable_dispose (GObject *object)
{
	BrowserVariable *bvar;

	g_return_if_fail (object != NULL);
	g_return_if_fail (BROWSER_IS_VARIABLE (object));

	bvar = BROWSER_VARIABLE (object);
	if (bvar->priv) {
		if (bvar->priv->holder)
			g_object_unref (bvar->priv->holder);

		g_free (bvar->priv);
		bvar->priv = NULL;
	}

	/* parent class */
	parent_class->dispose (object);
}