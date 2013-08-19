/******************************************************************************
 * This file is part of the libqgit2 library
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 * Copyright (C) 2013 Leonardo Giordani
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "qgittree.h"

#include "qgittreeentry.h"
#include "qgitrepository.h"
#include "qgitoid.h"

#include <QtCore/QFile>

namespace LibQGit2
{

QGitTree::QGitTree(git_tree *tree)
    : Object(reinterpret_cast<git_object*>(tree))
{
}

QGitTree::QGitTree( const QGitTree& other )
    : Object(other)
{
}

QGitTree::~QGitTree()
{
}

OId QGitTree::oid()
{
    return OId(git_tree_id(data()));
}

size_t QGitTree::entryCount()
{
    return git_tree_entrycount(data());
}

QGitTreeEntry QGitTree::entryByName(const QString& fileName) const
{
    return QGitTreeEntry(git_tree_entry_byname(data(), QFile::encodeName(fileName)));
}

QGitTreeEntry QGitTree::entryByIndex(int idx) const
{
    return QGitTreeEntry(git_tree_entry_byindex(data(), idx));
}

git_tree* QGitTree::data() const
{
    return reinterpret_cast<git_tree*>(Object::data());
}

const git_tree* QGitTree::constData() const
{
    return reinterpret_cast<git_tree*>(Object::data());
}

} // namespace LibQGit2
