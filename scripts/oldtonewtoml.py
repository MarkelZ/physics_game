import toml

# change these two and run script
path = 'ragdoll.toml'
path2 = 'ragdoll2.toml'


file = open(path)
parsed = toml.load(file)
vertices = parsed['geometry']['vertices']
links = parsed['geometry']['edges']

vertx = [v[0] for v in vertices]
verty = [v[1] for v in vertices]
left = [l[0] for l in links]
right = [l[1] for l in links]

newtomldic = {'vertices': {'xpos': vertx, 'ypos': verty},
              'links': {'left': left, 'right': right}}

file2 = open(path2, 'w')
toml.dump(newtomldic, file2)
