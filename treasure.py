def treasure_map(N, artifacts, searched):

    # this program takes in two strings representing coordinates for buried artifacts and areas that have been searched on a NxN grid and returns the number
    # of complete and the number of partial artifacts found.
    
    from collections import defaultdict

    artifact_count = 0
    complete_artifacts = 0
    partial_artifacts = 0

    artifacts_map_matrix = [['O' for col in range(N)] for row in range(N)]

    d = defaultdict(lambda: 0)

    artifactsArray = artifacts.split(',')
    for artifact_count, item in enumerate(artifactsArray):
            coords = item.split(' ')
            row_x = int(coords[0][:-1])
            col_x = ord(coords[0][-1])- (ord('A') -1)
            row_y= int(coords[1][:-1])
            col_y = ord(coords[1][-1]) - (ord('A') -1)

            for r in range(row_x, row_y +1):
                for c in range(col_x, col_y +1):
                    #print(f'{r}, {c}')
                    artifacts_map_matrix[r - 1][c - 1] = artifact_count
                    d[artifact_count] += 1

    found_artifacts =  defaultdict(lambda: 0)
    searchedArray = searched.split(' ')
    for item in searchedArray:
        row = int(item[:-1])
        col = ord(item[-1]) - (ord('A') -1)
        if artifacts_map_matrix[row - 1][col - 1] != 'O':
            found_artifacts[artifacts_map_matrix[row - 1][col - 1]] += 1

    for k in d.keys():
        if found_artifacts[k] == d[k]:
            complete_artifacts += 1
        elif found_artifacts[k] != 0:
            partial_artifacts += 1

    res = [complete_artifacts, partial_artifacts]

    return res

# test driver
if __name__ == '__main__':

    artifacts = "1B 2C,2D 4D" # map coordinates of buried artifacts
    searched = "2B 2D 3D 4D 4A" # where Jack has searched
    N = 4
    res = treasure_map(N, artifacts, searched) # expecting [1,1]
    print(res)

    artifacts = "1A 1B,2C 2C"
    searched = "1B"
    N = 3
    res = treasure_map(N, artifacts, searched) # expecting [0,1]
    print(res)

    artifacts = "1A 2A,12A 12A"
    searched = "12A"
    N = 12
    res = treasure_map(N, artifacts, searched) # expecting [0,1]
    print(res)
