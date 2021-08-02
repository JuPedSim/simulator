# a var to check if 2 floats are equal
accuracy =0.01
# generates a
def _calc_grid(polygon, distance):
    lines: list = []
    min_x, min_y, max_x, max_y = _get_min_max(polygon)
    x_len = max_x - min_x
    y_len = max_y - min_y
    x_n = int(x_len / distance) + 1
    y_n = int(y_len / distance) + 1
    for x in range(0, x_n):
        lines.append([[min_x + distance * x, min_y - distance], [min_x + distance * x, max_y + distance]])
    for y in range(0, y_n):
        lines.append([[min_x - distance, min_y + distance * y], [max_x + distance, min_y + distance * y]])
    return lines


# calculates the intersection(=point) of two lines- a line is a list of two points
def _find_intersection(line_0, line_1):
    p0, p1, p2, p3 = line_0[0], line_0[1], line_1[0], line_1[1]
    s10_x = p1[0] - p0[0]
    s10_y = p1[1] - p0[1]
    s32_x = p3[0] - p2[0]
    s32_y = p3[1] - p2[1]
    denom = float(s10_x * s32_y - s32_x * s10_y)
    if denom == 0: return None  # collinear
    denom_is_positive = denom >= 0
    s02_x = p0[0] - p2[0]
    s02_y = p0[1] - p2[1]
    s_numer = float(s10_x * s02_y - s10_y * s02_x)
    if (s_numer < 0) == denom_is_positive: return None  # no collision
    t_numer = float(s32_x * s02_y - s32_y * s02_x)
    if (t_numer < 0) == denom_is_positive: return None  # no collision
    if (s_numer > denom) == denom_is_positive or (t_numer > denom) == denom_is_positive: return None  # no collision
    # collision detected
    t = t_numer / denom
    intersection_point = [p0[0] + (t * s10_x), p0[1] + (t * s10_y)]
    return intersection_point


# calculates all intersections(list of points) of a list of lines(=list with 2 points)
# and those line with a polygon(=list of points)
def _calc_intersections(lines, polygon):
    points: list = []
    point_candidates: list = []
    for i, l0 in enumerate(lines):
        for j, l1 in enumerate(lines):
            if j == i: continue
            p = _find_intersection(l0, l1)
            if p is not None: point_candidates.append(p)
        p0 = polygon[0]
        for x in range(0, len(polygon)):
            l2 = [(p0), (polygon[len(polygon) - x - 1])]
            p0 = polygon[len(polygon) - x - 1]
            p = _find_intersection(l2, l0)
            if p is not None: points.append(p)
    for l1 in lines:
        p0 = polygon[0]
        for x in range(0, len(polygon)):
            l2 = [(p0), (polygon[len(polygon) - x - 1])]
            p0 = polygon[len(polygon) - x - 1]
            p = _find_intersection(l2, l1)
            if p is not None: points.append(p)
    return point_candidates, points


# counts how many times a line segment intersects with a polygon
def _count_intersections(point, polygon, x, y, fx, fy):
    line = ((x + fx, y + fy), (point[0] - accuracy * fx, point[1] + accuracy * fy))
    intersections = 0
    p0 = polygon[0]
    for x in range(0, len(polygon)):
        l2 = ((p0), (polygon[len(polygon) - x - 1]))
        p0 = polygon[len(polygon) - x - 1]
        p = _find_intersection(l2, line)
        if p is not None: intersections += 1
    return intersections


# a test if a point is in a polygon or outside
# start lines outside of the polygon and end them at the point to check
# if the number of intersection of this line and the polygon is even it's outside, otherwise it's inside
def _is_inside(point, polygon, min_x, min_y, max_x, max_y):
    intersections = _count_intersections(point, polygon, min_x, min_y, -1, -1)
    if (intersections % 2) == 0:
        intersections = _count_intersections(point, polygon, max_x, min_y, 1, -1)
    if (intersections % 2) == 0:
        intersections = _count_intersections(point, polygon, min_x, max_y, -1, 1)
    return (intersections % 2) != 0


# gets the biggest/smallest x/y values of a list of points
def _get_min_max(geometry):
    min_x, min_y, max_x, max_y = geometry[0][0], geometry[0][1], geometry[1][0], geometry[1][1]
    for point in geometry:
        if point[0] < min_x: min_x = point[0]
        if point[1] < min_y: min_y = point[1]
        if point[0] > max_x: max_x = point[0]
        if point[1] > max_y: max_y = point[1]
    return min_x, min_y, max_x, max_y


# checks if a point is either right(positive X) or up(positive Y) of another point by a certain distance
def _is_in_distance(point, p2, distance):
    is_up = False
    temp_p = [point[0], point[1]]
    temp_p[0] += distance
    is_right = _is_same_point(temp_p, p2)
    if not is_right:
        temp_p = [point[0], point[1]]
        temp_p[1] += distance
        is_up = _is_same_point(temp_p, p2)
    return is_right, is_up


# a check if two points are the same(with a margin)
def _is_same_point(p0, p1):
    return _is_same_float(p0[0], p1[0]) and _is_same_float(p0[1], p1[1])


# a check if two floats are the same(with a margin)
def _is_same_float(f0, f1):
    return abs(f0 - f1) < 1 * accuracy


# calculates the midpoint of a square
def _calc_midpoint(box, dist):
    return box[0][0] + dist / 2, box[0][1] + dist / 2


# for each point, find the corresponding points to get a square with the side length of the given distance
def _calc_boxes(points: list, distance: float):
    boxes: list = []
    n_found = 1
    for i, point in enumerate(points):
        box: list = [point, None, None, None]
        for j, p2 in enumerate(points):
            if i == j: continue
            isright, isup = _is_in_distance(point, p2, distance)
            if isup or isright:
                n_found += 1
                if isright:
                    box[3] = p2
                if isup:
                    box[1] = p2
                    for k, p3 in enumerate(points):
                        if k == j: continue
                        isright, isup = _is_in_distance(p2, p3, distance)
                        if isright:
                            n_found += 1
                            box[2] = p3
                            break
        if n_found == 4:
            boxes.append(box)
        n_found = 1
    return boxes


# iterates the list of points and removes duplicate points that are approximately the same
def _remove_duplicate_points(points: list):
    for i, p0 in enumerate(points):
        j = 0
        while j < len(points):
            if i == j:
                j += 1
                continue
            if _is_same_point(p0, points[j]):
                points.pop(j)
                j -= 1
            j += 1

# A polygon must met the contition that it has to consist of more than two points and its lines should not cross
def _find_polygon_err(polygon:list):
    if len(polygon)<3:
        return "Area must consist of more than 2 points"
    ip0 = polygon[0]
    if len(polygon)>3:
        for i in range(0, len(polygon)):
            l0 = [(ip0), (polygon[len(polygon) - i - 1])]
            ip0 = polygon[len(polygon) - i - 1]
            jp0 = polygon[0]
            for j in range(0, len(polygon)):
                l1 = [(jp0), (polygon[len(polygon) - j - 1])]
                jp0 = polygon[len(polygon) - j - 1]
                if i == j or i==(j+1)%len(polygon) or i==abs((j-1)%len(polygon)):continue
                p = _find_intersection(l1, l0)
                if p is not None: return "Polygon lines should not intersect"
    return None

def generate_spawn_points(polygon, distance):
    err=_find_polygon_err(polygon)
    if err is not None:
        return err
    lines = _calc_grid(polygon, distance)
    maybe_points, points = _calc_intersections(lines, polygon)
    minx, miny, maxx, maxy = _get_min_max(polygon)
    _remove_duplicate_points(maybe_points)
    for i in range(len(maybe_points) - 1, -1, -1):
        if not _is_inside(maybe_points[i], polygon, minx, miny, maxx, maxy):
            maybe_points.pop(i)
    points.extend(maybe_points)
    _remove_duplicate_points(points)
    boxes = _calc_boxes(points, distance)
    midpoints: list = []
    for box in boxes:
        midpoints.append(_calc_midpoint(box, distance))
    return midpoints
