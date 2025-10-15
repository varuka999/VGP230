#pragma once
#include <string>
#include <vector>

struct Ingredients;

struct Meal
{
    MealType mealType = Invalid;
    std::vector<Ingredient> ingredients;
    float TotalIngredientsPrice - 0.0f;

    CalculateIngredientsPrice();

    Meal();
    Meal(MealType type, std::vector<Ingredient> ingr);
};
