/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef UBCOOKIEJAR_H
#define UBCOOKIEJAR_H

#include <QtNetwork/QNetworkCookieJar>

#include <QtGui>

class UBAutoSaver;

class UBCookieJar : public QNetworkCookieJar
{
    friend class UBCookieModel;
    Q_OBJECT
    Q_PROPERTY(AcceptPolicy acceptPolicy READ acceptPolicy WRITE setAcceptPolicy)
    Q_PROPERTY(KeepPolicy keepPolicy READ keepPolicy WRITE setKeepPolicy)
    Q_PROPERTY(QStringList blockedCookies READ blockedCookies WRITE setBlockedCookies)
    Q_PROPERTY(QStringList allowedCookies READ allowedCookies WRITE setAllowedCookies)
    Q_PROPERTY(QStringList allowForSessionCookies READ allowForSessionCookies WRITE setAllowForSessionCookies)
    Q_ENUMS(KeepPolicy)
    Q_ENUMS(AcceptPolicy)

    signals:
        void cookiesChanged();

    public:
        enum AcceptPolicy {
            AcceptAlways,
            AcceptNever,
            AcceptOnlyFromSitesNavigatedTo
        };

        enum KeepPolicy {
            KeepUntilExpire,
            KeepUntilExit,
            KeepUntilTimeLimit
        };

        UBCookieJar(QObject *parent = 0);
        ~UBCookieJar();

        QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const;
        bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);

        AcceptPolicy acceptPolicy() const;
        void setAcceptPolicy(AcceptPolicy policy);

        KeepPolicy keepPolicy() const;
        void setKeepPolicy(KeepPolicy policy);

        QStringList blockedCookies() const;
        QStringList allowedCookies() const;
        QStringList allowForSessionCookies() const;

        void setBlockedCookies(const QStringList &list);
        void setAllowedCookies(const QStringList &list);
        void setAllowForSessionCookies(const QStringList &list);

    public slots:
        void clear();
        void loadSettings();

    private slots:
        void save();

    private:
        void purgeOldCookies();
        void load();
        bool mLoaded;
        UBAutoSaver *mSaveTimer;

        AcceptPolicy mAcceptCookies;
        KeepPolicy mKeepCookies;

        QStringList mExceptionsBlock;
        QStringList mExceptionsAllow;
        QStringList mExceptionsAllowForSession;
};


#endif // UBCOOKIEJAR_H

