/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "qgitcommit.h"

#include "qgitrepository.h"
#include "qgitsignature.h"
#include "qgittree.h"

using namespace LibQGit2;

QGitCommit::QGitCommit( QGitRepository *repository, QObject* parent)
{
    git_commit_new(&m_commit, repository->data());
}

QGitCommit::QGitCommit( const git_commit *commit, QObject* parent)
    : m_commit(const_cast<git_commit *>(m_commit))
{
}

QGitCommit::QGitCommit( const QGitCommit& other )
{
    m_commit = other.m_commit;
}

QGitCommit::~QGitCommit()
{
}

int QGitCommit::lookup(QGitRepository *repository, const QGitOId& oid)
{
    return git_commit_lookup(&m_commit, repository->data(), oid.constData());
}

const QGitOId* QGitCommit::id() const
{
    const QGitOId *oid = new QGitOId(git_commit_id(m_commit));
    return oid;
}

QString QGitCommit::messageShort() const
{
    return QString::fromUtf8(git_commit_message_short(m_commit));
}

QString QGitCommit::message() const
{
    return QString::fromUtf8(git_commit_message(m_commit));
}

QDateTime QGitCommit::dateTime() const
{
    QDateTime dateTime;
    dateTime.setTime_t(git_commit_time(m_commit));
    return dateTime;
}

int QGitCommit::timeOffset() const
{
    return git_commit_time_offset(m_commit);
}

const QGitSignature* QGitCommit::committer() const
{
    const QGitSignature *signature = new QGitSignature(git_commit_committer(m_commit));
    return signature;
}

const QGitSignature* QGitCommit::author() const
{
    const QGitSignature *signature = new QGitSignature(git_commit_author(m_commit));
    return signature;
}

const QGitTree* QGitCommit::tree() const
{
    const QGitTree *tree = new QGitTree(git_commit_tree(m_commit));
    return tree;
}

unsigned int QGitCommit::parentCount() const
{
    return git_commit_parentcount(m_commit);
}

QGitCommit* QGitCommit::parent(unsigned n) const
{
    QGitCommit *commit = new QGitCommit(git_commit_parent(m_commit, n));
    return commit;
}

int QGitCommit::addParent(QGitCommit* newParent)
{
    return git_commit_add_parent(m_commit, newParent->data());
}

void QGitCommit::setMessage(const QString& message)
{
    return git_commit_set_message(m_commit, message.toAscii().constData());
}

void QGitCommit::setCommitter(const QGitSignature& committerSig)
{
    return git_commit_set_committer(m_commit, committerSig.constData());
}

void QGitCommit::setAuthor(const QGitSignature& authorSig)
{
    return git_commit_set_author(m_commit, authorSig.constData());
}

void QGitCommit::setTree(const QGitTree& tree)
{
    return git_commit_set_tree(m_commit, tree.data());
}

git_commit* QGitCommit::data() const
{
    return m_commit;
}

const git_commit* QGitCommit::constData() const
{
    return const_cast<const git_commit *>(m_commit);
}
