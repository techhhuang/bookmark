#include <Log.h>
#include <View.h>

namespace SmartUI {

View::View()
    : mX(0),
      mY(0),
      mWidth(0),
      mHeight(0),
      mBgColor(Color(255, 255, 255, 255)),
      mVisible(true),
      mCliping(true) {}

void View::addChild(View* child) {
  TRACE("View addChild...\n");
  mChildren.push_back(child);
  child->setParent(this);
}

void View::draw(Context* ctx) {
  TRACE("View draw self...\n");
  // draw view self, draw border just for test
  ctx->beginPath();
  ctx->rect(mX, mY, mWidth, mHeight);
  ctx->fillColor(mBgColor);
  ctx->stroke();
  ctx->fill();

  if (mChildren.empty()) {
    return;
  }
  TRACE("View draw children:%ld\n", mChildren.size());
  ctx->save();
  ctx->translate(mX, mY);

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
}