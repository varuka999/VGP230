#include "Meal.h"
#include "Ingredient.h"

Meal::Meal()
{
}

Meal::Meal(MealType type, std::vector<Ingredient> ingr)
{
    mealType = type;
    ingredients = ingr;
    CalculateIngredientsPrice();
}

Meal::CalculateIngredientsPrice()
{
    foreach(Ingredient ingr in ingredients)
    {
        TotalIngredientsPrice += ingr.pricePerMeals;
    }
}
