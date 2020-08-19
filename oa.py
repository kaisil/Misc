def solution(N, artifacts, searched):

    #count # of complete artifacts
    #count # of partial artifacts
    # artifacts_map_matrix = [['O', 'O', 'O', 'O']
    # ['O', 'O', 'O', 'O']
    # ['O', 'O', 'O', 'O']
    # ['O', 'O', 'O', 'O']]
    from collections import defaultdict

    artifact_count = 0
    artifacts_map_matrix = [['O', 'O', 'O', 'O'] for row in range(4)]
    d = defaultdict(lambda: 0)
    complete_artifacts = 0
    partial_artifacts = 0

    for i in range(0,len(artifacts),6):
            row_x = ord(artifacts[i]) - ord('0') #rows are numeric: subtract ascii '0'
            col_x = ord(artifacts[(i + 1)])- (ord('A') -1) #cols are alpha: subtract 'A'
            row_y= ord(artifacts[(i + 3)]) - ord('0')
            col_y = ord(artifacts[(i + 4)]) - (ord('A') -1)

            artifact_count += 1

            for r in range(row_x, row_y +1):
                for c in range(col_x, col_y +1):
                    artifacts_map_matrix[r - 1][c - 1] = artifact_count
                    d[artifact_count] += 1
    for x in artifacts_map_matrix:
        print(x)
    found_artifacts =  defaultdict(lambda: 0)

    for i in range(0,len(searched), 3):
        row = ord(searched[i]) - ord('0')
        col = ord(searched[i + 1]) - (ord('A') -1)
        if artifacts_map_matrix[row - 1][col - 1] != 0:
            found_artifacts[artifacts_map_matrix[row - 1][col - 1]] += 1

    for k in d.keys():
        if found_artifacts[k] == d[k]:
            complete_artifacts += 1
        elif found_artifacts[k] != 0:
            partial_artifacts += 1

    res = [complete_artifacts, partial_artifacts]

    return res

if __name__ == '__main__':

    artifacts = "1B 2C,2D 4D" # map coordinates of buried artifacts
    searched = "2B 2D 3D 4D 4A" # where Jack has searched
    N = 4
    res = solution(N, artifacts, searched) # expecting [1,1]
    print(res)

    artifacts = "1A 1B,2C 2C" # map coordinates of buried artifacts
    searched = "1B" # where Jack has searched
    N = 3
    res = solution(N, artifacts, searched) # expecting [0,1]
    print(res)

