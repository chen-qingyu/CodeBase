#include <math.h>
#include <stdio.h>

#define PI 3.1415926

struct rect
{
    double x;
    double y;
};

struct polar
{
    double radius;
    double angle;
};

struct polar rect_to_polar(struct rect r)
{
    struct polar p;
    p.radius = sqrt(r.x * r.x + r.y * r.y);
    p.angle = (180 / PI) * atan2(r.y, r.x);
    return p;
}

struct rect polar_to_rect(struct polar p)
{
    struct rect r;
    r.x = p.radius * cos(p.angle * PI / 180);
    r.y = p.radius * sin(p.angle * PI / 180);
    return r;
}

int main(void)
{
    int choice;
    printf("Rectangular to polar coordinates: 1\n");
    printf("Polar to rectangular coordinates: 2\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        struct rect input;
        printf("(x, y) = ");
        scanf("%lf %lf", &input.x, &input.y);

        struct polar result = rect_to_polar(input);

        printf("(radius, angle(degree)) = (%.2lf, %.2lf)\n", result.radius, result.angle);
    }
    else if (choice == 2)
    {
        struct polar input;
        printf("(radius, angle(degree)) = ");
        scanf("%lf %lf", &input.radius, &input.angle);

        struct rect result = polar_to_rect(input);

        printf("(x, y) = (%.2lf, %.2lf)\n", result.x, result.y);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
