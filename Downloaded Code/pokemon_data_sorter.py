import pandas as pd

# df = data frame
df = pd.read_csv('pokemon_data.csv')

# print(df)
# print(df.head(5)) prints first 5 rows
# print(df.tail(5)) prints last 5 rows

## Read Headers
print(df.columns) # will print the headers of each column

## Read Each Column
print(df['Name']) #prints just the name column

## Read Each Row
print(df.iloc[1:4]) #iloc means integer location, will print rows 1-4
for index, row in df.iterrows():
    print(index, row)

print(df.loc[df['Type 1'] == "Fire"])

## Read a specific location (R, C)
print(df.iloc[2, 1]) #prints second row, first position

## Gives numerical data (mean, std, min, max)
# df.describe

## Sort values
# df.sort_values('Name') sorts alphabetically
## can sort by multiple rows:
# df.sort_values(['Type 1', 'HP'], ascending=[1,0])

## can make new column that is the sum of other columns
df['Total'] = df['HP'] + df['Attack'] + df['Defense'] + df['Sp. Atk'] + df['Sp. Def'] + df['Speed']

## drop a specific column
df = df.drop(columns=['Total'])
## can also be done this way:
df['Total'] = df.iloc[:, 4:10].sum(axis=1) #axis = 1 is horizontally, 0 is vertically

## can move total row from end to somewhere else
cols = list(df.columns.values)
df = df[cols[0:4] + [cols[-1]] + cols[4:12]]

## saving a new edited csv
# df.to_csv('modified.csv', index = False) #index = false removes an index column that it makes when making the new csv

## more advanced filtering
# new_df = df.loc[(df['Type 1'] == 'Grass') & (df['Type 2'] == 'Poison') & (df['HP'] > 70)] # will get only pokemon that are both grass and poison type
# print(new_df)
# new_df.to_csv('filtered.csv')
# new_df = new_df.reset_index() sets indexing back at 0 instead of the old ones

## filter out mega evolutions (use ~ not !) for .loc
# df.loc[~df['Name'].str.contains('Mega')]

## filtering using regular expressions:
# df.loc[df['Name'].str.contains('^pi[a-z]*', flags=re.I, regex=True)] #gets all pokemon that start with "pi"

## can sort by groups as well
# df.groupby(['Type 1']).mean().sort_values('Attack', ascending=False)
# will sort in descending order each type to see which type has the highest atk, def, etc

## can use .count() to see how many of each type their are

## loading in chunks:
# new_df = pd.DataFrame(columns=df.columns)
# for df in pd.read_csv('modified.csv', chunksize=100): # reads in 100 rows as a chunk
#       results = df.groupby(['Type 1']).count()
#
#       new_df = pd.concat([new_df, results])


