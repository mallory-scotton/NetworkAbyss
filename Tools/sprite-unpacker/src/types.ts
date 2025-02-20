/** Utility type for Vec2 */
export type UnityVec2 = {
  x?: number;
  y?: number;
}

/** Utility type for Vec3 */
export type UnityVec3 = UnityVec2 & {
  z?: number;
}

/** Utility type for Vec4 */
export type UnityVec4 = UnityVec3 & {
  w?: number;
}

/** Utility type for rectangles shape */
export type UnityRect = UnityVec2 & {
  width?: number;
  height?: number;
}

/** Utility type for unity files reference */
export type UnityFile = {
  fileID?: number;
  guid?: string;
  type?: number;
}

/** Unity sprite metadata type alias */
export type UnitySprite = {
  Sprite: {
    m_Name?: string;
    m_Rect?: UnityRect;
    m_Offset?: UnityVec2;
    m_Border?: UnityVec4;
    m_PixelsToUnits?: number;
    m_Pivot?: UnityVec2;
    m_RD?: {
      texture?: UnityFile;
      textureRect?: UnityRect;
      textureRectOffset?: UnityVec2;
      atlasRectOffset?: UnityVec2;
      uvTransform?: UnityVec4;
    }
  }
}

/** Utility type for texture metadata */
export type UnityTexture = {
  path?: string;
  guid?: string;
};
