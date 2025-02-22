// class EffectManager {
//     public:
//         void addEffect(const Effect& effect) {
//             activeEffects[effect.type].push_back(effect);
//             recalculateEffects();
//         }
    
//         void removeEffect(const Effect& effect) {
//             auto& effects = activeEffects[effect.type];
//             effects.erase(std::remove_if(effects.begin(), effects.end(),
//                 [&effect](const Effect& e) { return e.value == effect.value; }),
//                 effects.end());
//             recalculateEffects();
//         }
    
//         float getEffectValue(EffectType type) const {
//             return finalEffectValues.count(type) ? finalEffectValues.at(type) : 0.0f;
//         }
    
//     private:
//         std::unordered_map<EffectType, std::vector<Effect>> activeEffects;
//         std::unordered_map<EffectType, float> finalEffectValues;
    
//         void recalculateEffects() {
//             finalEffectValues.clear();
    
//             for (const auto& [type, effects] : activeEffects) {
//                 if (effects.empty()) continue;
    
//                 float finalValue = 0.0f;
//                 StackingBehavior behavior = effects[0].stackingBehavior;
    
//                 switch (behavior) {
//                     case StackingBehavior::ADDITIVE:
//                         for (const auto& effect : effects) {
//                             finalValue += effect.value;
//                         }
//                         break;
    
//                     case StackingBehavior::MULTIPLICATIVE:
//                         finalValue = 1.0f;
//                         for (const auto& effect : effects) {
//                             finalValue *= (1.0f + effect.value);
//                         }
//                         finalValue -= 1.0f;
//                         break;
    
//                     case StackingBehavior::MAXIMUM:
//                         finalValue = effects[0].value;
//                         for (const auto& effect : effects) {
//                             finalValue = std::max(finalValue, effect.value);
//                         }
//                         break;
    
//                     case StackingBehavior::OVERRIDE:
//                         finalValue = effects.back().value;
//                         break;
//                 }
    
//                 finalEffectValues[type] = finalValue;
//             }
//         }
//     };
    