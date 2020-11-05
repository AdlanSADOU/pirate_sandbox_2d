// #include "game.h"

// /*
//     Abstraction over S2D_Sprite
//     do not attempt to modify sprite pointer directly. The values will not be reflected in S2D_IRect and S2D_vec2i
// */
// sdEntity *sdEntityCreate(const char *path)
// {
//     sdEntity *entity = (sdEntity *)malloc(sizeof(sdEntity));
//     if (!entity) {
//         printf("Entity malloc failed %d %s", __LINE__, __FILE__);
//         return NULL;
//     }
    
//     S2D_Sprite *sprite = S2D_CreateSprite(path);
//     if (!sprite) {
//         printf("Sprite creation failed %d %s", __LINE__, __FILE__);
//         free(entity);
//         return NULL;
//     }

//     entity->rect.x = sprite->x;
//     entity->rect.y = sprite->y;
//     entity->rect.width = sprite->width;
//     entity->rect.height = sprite->height;
//     entity->sprite = sprite;
//     return entity;
// }

// void sdEntityDraw(sdEntity *entity, bool debugMode)
// {
//     S2D_FRect rect = entity->rect;

//     GLfloat x1 = rect.x,                y1 = rect.y;
//     GLfloat x2 = rect.x + rect.width,   y2 = rect.y;
//     GLfloat x3 = rect.x + rect.width,   y3 = rect.y + rect.height;
//     GLfloat x4 = rect.x,                y4 = rect.y + rect.height;

//     S2D_Color color = { 1.0f, 0.5f, 0.5f, 1.0f };

//     if (debugMode) S2D_DrawRect(rect, color, true);

//     S2D_DrawSprite(entity->sprite);
// }

// void sdEntitySetSize(sdEntity *entity, float width, float height)
// {
//     entity->sprite->width = width;
//     entity->sprite->height = height;
//     entity->rect.width = width;
//     entity->rect.height = height;
// }

// void sdEntityMove(sdEntity *entity, float x, float y)
// {
//     entity->sprite->x += x;
//     entity->sprite->y += y;
//     entity->position.x += x;
//     entity->position.y += y;
//     entity->rect.x += x;
//     entity->rect.y += y;
// }

// void sdEntitySetPosition(sdEntity *entity, float x, float y)
// {
//     entity->sprite->x = x;
//     entity->sprite->y = y;
//     entity->position.x = x;
//     entity->position.y = y;
//     entity->rect.x = x;
//     entity->rect.y = y;
// }