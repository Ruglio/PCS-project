import src.SegmentClass as SG


class IPolygon:
    def get_number_vertices(self):
        pass

    def get_vertices(self):
        pass

    def set_vertex_at_position(self, vertex, position):
        pass

    def append_vertex(self, vertex):
        pass

    def insert_vertex_at_position(self, vertex, position):
        pass

    def get_vertex_at_position(self, position):
        pass

    def next_vertex_id(self, id):
        pass

    def get_last_vertex(self):
        pass

    def get_edges(self):
        pass

    def set_vertex_label_at_position(self, position, label):
        pass

    def get_point_label_at_position(self, position):
        pass

    def set_vertices_label(self, polygon_vertices):
        pass

    def set_default_vertices_label(self):
        pass


class Polygon(IPolygon):
    def __init__(self, vertices):
        self.__number_vertices = len(vertices)
        self.__vertices = vertices
        self.__edges = []

        for i in range(0, self.__number_vertices):
            if i == (self.__number_vertices - 1):
                self.__edges.append(SG.Segment(self.__vertices[i], self.__vertices[0]))
            else:
                self.__edges.append(SG.Segment(self.__vertices[i], self.__vertices[i + 1]))

    def get_number_vertices(self):
        return self.__number_vertices

    def get_vertices(self):
        return self.__vertices

    def set_vertex_at_position(self, vertex, position):
        self.__vertices[position] = vertex

    def append_vertex(self, vertex):
        self.__vertices.append(vertex)
        self.__number_vertices = len(self.__vertices)

    def insert_vertex_at_position(self, vertex, position):
        self.__vertices.insert(position, vertex)
        self.__number_vertices = len(self.__vertices)

    def get_vertex_at_position(self, position):
        return self.__vertices[position]

    def next_vertex_id(self, id):
        if id < 0 or id >= self.__number_vertices:
            raise ValueError("Vertex id is not present")

        if id == self.__number_vertices - 1:
            return 0

        else:
            return id + 1

    def get_last_vertex(self):
        return self.__vertices[self.__number_vertices - 1]

    def get_edges(self):
        return self.__edges

    def set_vertex_label_at_position(self, position, label):
        self.__vertices[position].set_point_label(label)

    def get_point_label_at_position(self, position):
        return self.__vertices[position].get_point_label()

    def set_vertices_label(self, polygon_vertices):
        for i in range(0, self.__number_vertices):
            label = polygon_vertices[i]
            self.__vertices[i].set_point_label(label)

    def set_default_vertices_label(self):
        for i in range(0, self.__number_vertices):
            self.__vertices[i].set_point_label(i)
