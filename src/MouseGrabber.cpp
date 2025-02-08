#include "MouseGrabber.hpp"
#include <QLoggingCategory>
#include <QCoreApplication>
#include <QHoverEvent>
#include <QMouseEvent>

using namespace wekde;

MouseGrabber::MouseGrabber(QQuickItem* parent): QQuickItem(parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

bool MouseGrabber::forceCapture() const { return m_forceCapture; }

QQuickItem* MouseGrabber::target() const { return m_target; }

void MouseGrabber::setForceCapture(bool value) {
    if (value == m_forceCapture) return;
    m_forceCapture = value;
    if (value) {
        grabMouse();
    } else {
        ungrabMouse();
    }
    Q_EMIT forceCaptureChanged();
}

void MouseGrabber::setTarget(QQuickItem* item) {
    if (item == m_target) return;
    m_target = item;
    if (m_target) m_target->setAcceptedMouseButtons(Qt::LeftButton);
    Q_EMIT targetChanged();
}

void MouseGrabber::mouseUngrabEvent() {
    if (m_forceCapture) grabMouse();
}

void MouseGrabber::sendEvent(QObject* target, QEvent* event) {
    QCoreApplication::sendEvent(target, event);
}

void MouseGrabber::sendMouseEvent(QMouseEvent* event) {
    if (m_target) {
        QMouseEvent temp(event->type(),
                         mapToItem(m_target, event->position()),
                         event->globalPosition(),
                         event->button(),
                         event->buttons(),
                         event->modifiers());
        QCoreApplication::sendEvent(m_target, &temp);
    }
}

void MouseGrabber::sendHoverEvent(QHoverEvent* event) {
    if (m_target) {
        QHoverEvent temp(event->type(),
                         mapToItem(m_target, event->position()),
                         mapToItem(m_target, event->oldPosF()),
                         event->modifiers());
        QCoreApplication::sendEvent(m_target, &temp);
    }
}

void MouseGrabber::sendWheelEvent(QWheelEvent* event) {
    if (m_target) {
        QWheelEvent temp(mapToItem(m_target, event->position()),
                         mapToItem(m_target, event->globalPosition()),
                         event->pixelDelta(),
                         event->angleDelta(),
                         event->buttons(),
                         event->modifiers(),
                         event->phase(),
                         event->inverted(),
                         event->source(),
                         event->pointingDevice());
        QCoreApplication::sendEvent(m_target, &temp);
    }
}

void MouseGrabber::mousePressEvent(QMouseEvent* event) {
    sendMouseEvent(event);
    // need accept press to receive release
    // this break long press on desktop
    event->accept();
}

void MouseGrabber::mouseMoveEvent(QMouseEvent* event) {
    sendMouseEvent(event);
    event->ignore();
}

void MouseGrabber::mouseReleaseEvent(QMouseEvent* event) {
    sendMouseEvent(event);
    event->ignore();
}

void MouseGrabber::mouseDoubleClickEvent(QMouseEvent* event) {
    sendMouseEvent(event);
    event->ignore();
}

void MouseGrabber::hoverMoveEvent(QHoverEvent* event) {
    sendHoverEvent(event);
    event->ignore();
}
