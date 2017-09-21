#include <Log.h>
#include <View.h>

namespace SmartUI {

View::View()
    : mPosition(0, 0),
      mWidth(0),
      mHeight(0),
      mBgColor(Color(255, 255, 255, 255)),
      mBgColorPressed(Color(255, 0, 255, 100)),
      mVisible(true),
      mCliping(true),
      mPressed(false) {}

void View::addChild(View* child) {
  TRACE("View addChild...\n");
  mChildren.push_back(child);
  child->setParent(this);
}

void View::draw(Context* ctx) {
  TRACE("View draw self...\n");
  // draw view self, draw border just for test
  ctx->beginPath();
  ctx->rect(x(), y(), mWidth, mHeight);
  if (mPressed) {
    ctx->fillColor(mBgColorPressed);
  } else {
    ctx->fillColor(mBgColor);
  }
  ctx->stroke();
  ctx->fill();

  if (mChildren.empty()) {
    return;
  }
  TRACE("View draw children:%ld\n", mChildren.size());
  ctx->save();
  ctx->translate(x(), y());

  for (auto child : mChildren) {
    if (child->mVisible) {
      ctx->save();
      if (child->mCliping) {
        ctx->clip(child->x(), child->y(), child->width(), child->height());
      }
      child->draw(ctx);
      ctx->restore();
    }
  }

  ctx->restore();
}

View* View::findView(Point<int> p) {
  TRACE("find at:%d %d view:%d %d %d %d children:%d \n", p.x(), p.y(),
        mPosition.x(), mPosition.y(), mWidth, mHeight, mChildren.size());
  for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
    View* child = *it;
    if (child->visible() && child->contains(p - mPosition))
      return child->findView(p - mPosition);
  }
  return contains(p) ? this : nullptr;
}
void View::onTouchDown(int id, int x, int y, unsigned int time) {
  TRACE("view onTouchDown:%d %d %d %u\n", id, x, y, time);
}
void View::onTouchUp(int id, int x, int y, unsigned int time) {
  TRACE("view onTouchUp:%d %d %d %u\n", id, x, y, time);
}
void View::onTouchMove(int id, int x, int y, unsigned int time) {
  TRACE("view onTouchMove:%d %d %d %u\n", id, x, y, time);
}
// void View::mouseButtonEvent(int button, int state, unsigned int time) {
//   TRACE("View mouseButtonEvent:%d %d %u\n", button, state, time);
//   if (state == 0) {
//     mPressed = false;
//   } else {
//     mPressed = true;
//   }
// }
}