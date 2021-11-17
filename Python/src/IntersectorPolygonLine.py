import src.PolygonClass as PLG
import src.Intersector1D1D as INTSEC
import collections as co
import src.PointClass as PC
import src.CONSTANT as CONST


class IIntersectorPolygonLine:
    def find_intersection_vertices(self):
        pass

    def find_polygons(self):
        pass

    def get_extended_polygons(self):
        pass

    def find_new_points(self):
        pass

    def extended_polygon_if_end_points_on_edge(self, num_poly, first_intersection_id, second_intersection_id, forward_direction):
        pass

    def check_in_conic_combination(self, line: PLG.SG.PC.np.array, v1: PLG.SG.PC.np.array, v2: PLG.SG.PC.np.array,
                                   flag: int):
        pass

    def search_key_index(self, multimap, key):
        pass


class intersector_polygon_line(IIntersectorPolygonLine):
    def __init__(self, intersector: INTSEC.IIntersector1D1D, polygon: PLG.IPolygon, segment: PLG.SG.ISegment):
        self.__intersector = intersector
        self.__polygon = polygon
        self.__line = segment
        self.__intersection_vertices = []
        self.__new_points = []
        self.__extended_new_polygons = []
        self.__new_polygons = []
        self.__intersection_id_to_segment_id = []
        self.__segment_id_to_intersection_id = []
        self.__found_vertex = []
        self.__start_found = False
        self.__end_found = False
        self.__flag = []
        self.__mmap_parametric_coordinate_to_intersection_point = []
        self.__mmap_parametric_coordinate_to_segment_id = []
        self.__map_segment_id_to_parametric_coordinate = co.OrderedDict()
        self.__map_intersection_id_to_parametric_coordinate = co.OrderedDict()

        for i in range(0, polygon.get_number_vertices()):
            self.__segment_id_to_intersection_id.append(-1)
            self.__found_vertex.append(False)
            self.__flag.append(0)

        self.__intersector.set_first_segment(segment.get_start().get_coordinates(), segment.get_end().get_coordinates())

    def find_intersection_vertices(self):
        edges = self.__polygon.get_edges()
        self.__polygon.set_default_vertices_label()
        self.__line.get_start().set_point_label(self.__polygon.get_number_vertices())
        self.__line.get_end().set_point_label(self.__polygon.get_number_vertices() + 1)

        for i in range(0, self.__polygon.get_number_vertices()):
            self.__intersector.set_second_segment(edges[i].get_start().get_coordinates(),
                                                  edges[i].get_end().get_coordinates())
            if (self.__intersector.compute_intersection() == True):
                intersection = self.__intersector.intersection_first_parametric_coordinate(
                    self.__line.get_start().get_coordinates(), self.__line.get_end().get_coordinates())
                s = self.__intersector.first_parametric_coordinate()
                if (self.search_key_index(self.__mmap_parametric_coordinate_to_intersection_point, s) == len(self.__mmap_parametric_coordinate_to_intersection_point)):
                    self.__mmap_parametric_coordinate_to_intersection_point.append((s, PC.Point(intersection)))
                    self.__mmap_parametric_coordinate_to_intersection_point = sorted(self.__mmap_parametric_coordinate_to_intersection_point)
                    self.__mmap_parametric_coordinate_to_segment_id.append((s, i))
                    self.__mmap_parametric_coordinate_to_segment_id = sorted(self.__mmap_parametric_coordinate_to_segment_id)
                    self.__map_segment_id_to_parametric_coordinate[i] = s
                    self.__map_segment_id_to_parametric_coordinate = co.OrderedDict(sorted(self.__map_segment_id_to_parametric_coordinate.items()))
                else:
                    is_in_conic = self.check_in_conic_combination(self.__line.compute_tangent(), edges[i - 1].get_tangent(), edges[i].get_tangent(), i)

                    if(is_in_conic == True):
                        self.__mmap_parametric_coordinate_to_intersection_point.append((s, PC.Point(intersection)))
                        self.__mmap_parametric_coordinate_to_intersection_point = sorted(self.__mmap_parametric_coordinate_to_intersection_point)
                        self.__mmap_parametric_coordinate_to_segment_id.append((s, i))
                        self.__mmap_parametric_coordinate_to_segment_id = sorted(self.__mmap_parametric_coordinate_to_segment_id)
                        self.__map_segment_id_to_parametric_coordinate[i] = s
                        self.__map_segment_id_to_parametric_coordinate = co.OrderedDict(sorted(self.__map_segment_id_to_parametric_coordinate.items()))

        for i in range(0, len(self.__mmap_parametric_coordinate_to_intersection_point)):
            self.__intersection_vertices.append(self.__mmap_parametric_coordinate_to_intersection_point[i][1])
            self.__intersection_vertices[i].set_point_label(self.__polygon.get_number_vertices() + 2 + i)

        for i in range(0, len(self.__mmap_parametric_coordinate_to_segment_id)):
                self.__intersection_id_to_segment_id.append(self.__mmap_parametric_coordinate_to_segment_id[i][1])
                self.__segment_id_to_intersection_id[self.__mmap_parametric_coordinate_to_segment_id[i][1]] = i

        for i in range(0, len(self.__intersection_id_to_segment_id)):
            segment_position = self.__intersection_id_to_segment_id[i]
            segment_start_point: PC.Point = edges[segment_position].get_start()
            if(self.__intersection_vertices[i] == segment_start_point):
                self.__intersection_vertices[i].set_point_label(segment_start_point.get_point_label())

            segment_end_point = edges[segment_position].get_end()
            if(self.__intersection_vertices[i] == segment_end_point):
                self.__intersection_vertices[i].set_point_label(segment_end_point.get_point_label())

        for i in range(0, len(self.__intersection_id_to_segment_id)):
            parametric_coordinate = self.__map_segment_id_to_parametric_coordinate[self.__intersection_id_to_segment_id[i]]
            self.__map_intersection_id_to_parametric_coordinate[i] = parametric_coordinate
            self.__map_intersection_id_to_parametric_coordinate = co.OrderedDict(sorted(self.__map_intersection_id_to_parametric_coordinate.items()))

        if (len(self.__intersection_vertices) % 2 == 1):
            raise ValueError ("errore nel numero dei vertici: vertici dispari")

        return self.__intersection_vertices




    def find_polygons(self):
        if(len(self.__intersection_vertices) == 0):
            raise ValueError ("first you need to find intersection vertices")

        new_polygons = self.__new_polygons
        extended_new_polygons = self.__extended_new_polygons
        vertices = self.__polygon.get_vertices()
        num_poly = 0

        for i in range(0, len(self.__found_vertex)):

            if(self.__found_vertex[i] == False):
                new_polygons.append(PLG.Polygon([]))
                extended_new_polygons.append(PLG.Polygon([]))
                id = i

                while True:
                    if(self.__segment_id_to_intersection_id[id] == -1):
                        new_polygons[num_poly].append_vertex(vertices[id])
                        extended_new_polygons[num_poly].append_vertex(vertices[id])

                        self.__found_vertex[id] = True
                        id = self.__polygon.next_vertex_id(id)

                    else:
                        new_polygons[num_poly].append_vertex(vertices[id])
                        extended_new_polygons[num_poly].append_vertex(vertices[id])

                        self.__found_vertex[id] = True
                        intersection_id = self.__segment_id_to_intersection_id[id]

                        if(self.__intersection_vertices[intersection_id] != vertices[id]):
                            new_polygons[num_poly].append_vertex(self.__intersection_vertices[intersection_id])
                            extended_new_polygons[num_poly].append_vertex(self.__intersection_vertices[intersection_id])

                        if(intersection_id % 2 == 0):
                            forward_direction = True
                            first_intersection_id = intersection_id
                            second_intersection_id = intersection_id + 1
                            self.extended_polygon_if_end_points_on_edge(num_poly, first_intersection_id, second_intersection_id, forward_direction)
                            intersection_id += 1

                        else:
                            forward_direction = False
                            first_intersection_id = intersection_id - 1
                            second_intersection_id = intersection_id
                            self.extended_polygon_if_end_points_on_edge(num_poly, first_intersection_id, second_intersection_id, forward_direction)
                            intersection_id -= 1

                        id = self.__intersection_id_to_segment_id[intersection_id]
                        if(self.__intersection_vertices[intersection_id] != vertices[self.__polygon.next_vertex_id(id)]):

                            if((forward_direction and self.__intersection_vertices[intersection_id] == self.__intersection_vertices[intersection_id - 1])
                            or ((not forward_direction) and self.__intersection_vertices[intersection_id] == self.__intersection_vertices[intersection_id + 1])):
                                self.__found_vertex[id] = True

                            else:
                                new_polygons[num_poly].append_vertex(self.__intersection_vertices[intersection_id])
                                extended_new_polygons[num_poly].append_vertex(self.__intersection_vertices[intersection_id])

                        id = self.__polygon.next_vertex_id(id)
                    if(id == i):
                        break
                num_poly = num_poly + 1
        return new_polygons


    def get_intersection_vertices(self):
        return self.__intersection_vertices

    def get_new_point(self):
        return self.__new_points

    def get_extended_polygons(self):
        return self.__extended_new_polygons

    def find_new_points(self):
        if (self.__start_found == True):
            self.__new_points.append(self.__line.get_start())
        if (self.__end_found == True):
            self.__new_points.append(self.__line.get_end())

        for i in range (0, len(self.__intersection_vertices)):
            segment_position = self.__intersection_id_to_segment_id[i]
            segment_start_point = self.__polygon.get_edges()[segment_position].get_start()
            segment_end_point = self.__polygon.get_edges()[segment_position].get_end()

            if (self.__intersection_vertices[i] != segment_start_point and self.__intersection_vertices[i] != segment_end_point):
                self.__new_points.append(self.__intersection_vertices[i])

        return self.__new_points

    def extended_polygon_if_end_points_on_edge(self, num_poly, first_intersection_id, second_intersection_id, forward_direction):

        if(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] < 0 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] > 0 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] < 1):
            self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
            self.__start_found = True

        elif(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] < 0 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] > 1):
            if(forward_direction == True):
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
                self.__start_found = True
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
                self.__end_found = True

            else:
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
                self.__end_found = True
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
                self.__start_found = True

        elif(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] > 0 and self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] < 1 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] > 1):
            self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
            self.__end_found = True

        elif(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] > 0 and self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] < 1 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] < 0):
            self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
            self.__start_found = True

        elif(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] > 1 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] < 0):
            if(forward_direction == True):
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
                self.__end_found =True
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
                self.__start_found = True

            else:
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_start())
                self.__start_found = True
                self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
                self.__end_found = True

        elif(self.__map_intersection_id_to_parametric_coordinate[first_intersection_id] > 1 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] < 1 and self.__map_intersection_id_to_parametric_coordinate[second_intersection_id] > 0):
            self.__extended_new_polygons[num_poly].append_vertex(self.__line.get_end())
            self.__end_found = True


    def check_in_conic_combination(self, line, v1, v2, i):
        nline = line / PLG.SG.PC.np.linalg.norm(line)
        nv1 = v1 / PLG.SG.PC.np.linalg.norm(v1)
        nv2 = v2 / PLG.SG.PC.np.linalg.norm(v2)
        bisector = nv1 + nv2
        bisector = bisector / PLG.SG.PC.np.linalg.norm(bisector)
        theta = INTSEC.math.acos(PLG.SG.PC.np.dot(bisector, nv1))
        alpha = INTSEC.math.acos(PLG.SG.PC.np.dot(bisector, nline))

        if (alpha < theta):
            self.__flag[i] = 1
            return True

        elif ( alpha > INTSEC.math.pi/2 and (INTSEC.math.pi-alpha) < theta):
            self.__flag[i] = -1
            return True

        self.__flag[i] = 0
        return False

    def search_key_index(self, multimap, key):
        temp1 = False
        temp2 = 0
        for i in range (0, len(multimap)):
            if abs(multimap[i][0] - key) < CONST.POINT_TOLERANCE:
                temp1 = True
                temp2 = i
                break

        if(temp1 == True):
            return temp2

        else:
            return len(multimap)


