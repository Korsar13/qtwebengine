// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QWEBENGINEFILESYSTEMACCESSREQUEST_H
#define QWEBENGINEFILESYSTEMACCESSREQUEST_H

#include <QtWebEngineCore/qtwebenginecoreglobal.h>

#include <QtCore/qsharedpointer.h>
#include <QtCore/qurl.h>

namespace QtWebEngineCore {
class FileSystemAccessPermissionRequestController;
class FileSystemAccessPermissionRequestManagerQt;
}

QT_BEGIN_NAMESPACE

class Q_WEBENGINECORE_EXPORT QWebEngineFileSystemAccessRequest
{
    Q_GADGET
    Q_PROPERTY(QUrl origin READ origin CONSTANT FINAL)
    Q_PROPERTY(QUrl filePath READ filePath CONSTANT FINAL)
    Q_PROPERTY(HandleType handleType READ handleType CONSTANT FINAL)
    Q_PROPERTY(AccessFlags accessFlags READ accessFlags CONSTANT FINAL)

public:
    QWebEngineFileSystemAccessRequest(const QWebEngineFileSystemAccessRequest &other);
    QWebEngineFileSystemAccessRequest &operator=(const QWebEngineFileSystemAccessRequest &other);
    QWebEngineFileSystemAccessRequest(QWebEngineFileSystemAccessRequest &&other);
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QWebEngineFileSystemAccessRequest)
    ~QWebEngineFileSystemAccessRequest();

    void swap(QWebEngineFileSystemAccessRequest &other) noexcept { d_ptr.swap(other.d_ptr); }

    enum HandleType { File, Directory };
    Q_ENUM(HandleType)

    enum AccessFlag { Read = 0x1, Write = 0x2 };
    Q_DECLARE_FLAGS(AccessFlags, AccessFlag)
    Q_FLAG(AccessFlags)

    Q_INVOKABLE void accept();
    Q_INVOKABLE void reject();
    QUrl origin() const;
    QUrl filePath() const;
    HandleType handleType() const;
    AccessFlags accessFlags() const;

    bool operator==(const QWebEngineFileSystemAccessRequest &that) const;
    bool operator!=(const QWebEngineFileSystemAccessRequest &that) const;

private:
    QWebEngineFileSystemAccessRequest(
            QSharedPointer<QtWebEngineCore::FileSystemAccessPermissionRequestController>);
    friend QtWebEngineCore::FileSystemAccessPermissionRequestManagerQt;

    QSharedPointer<QtWebEngineCore::FileSystemAccessPermissionRequestController> d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QWebEngineFileSystemAccessRequest::AccessFlags)

QT_END_NAMESPACE

#endif // QWEBENGINEFILESYSTEMACCESSREQUEST_H
