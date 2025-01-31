package main

import (
	"fmt"
	"sort"
	"time"
)

type servData struct {
	name   string
	numAtt int
	result int
}

type teamData struct {
	name    string
	penalty int
	hacked  int
	data    []servData
}

func main() {
	var submNum int
	var sTime string
	offset := 23*time.Hour + 59*time.Minute + 59*time.Second
	layout := "15:04:05"

	fmt.Scan(&sTime)
	starting, err := time.Parse(layout, sTime)
	if err != nil {
		fmt.Printf("Invalid time format: %v\n", err)
		return
	}
	ending := starting.Add(offset)

	fmt.Scan(&submNum)
	teams := make(map[string]teamData)

	for i := 0; i < submNum; i++ {
		var tName, tAprv, svName, svFlag string
		fmt.Scanf("%s %s %s %s", &tName, &tAprv, &svName, &svFlag)
		//fmt.Println(tName, tAprv, svName, svFlag

		team, exists := teams[tName]
		if !exists {
			team = teamData{name: tName}
		}

		evTime, err := time.Parse(layout, tAprv)
		if err != nil {
			fmt.Printf("Invalid time format: %v\n", err)
			return
		}

		if evTime.After(ending) {
			continue
		}

		if evTime.Before(starting) {
			evTime = evTime.Add(24 * time.Hour)
		}

		svIndex := -1
		for i, serv := range team.data {
			if svName == serv.name {
				svIndex = i
				break
			}
		}

		if svIndex == -1 {
			team.data = append(team.data, servData{name: svName})
			svIndex = len(team.data) - 1
		}

		if svFlag == "DENIED" || svFlag == "FORBIDEN" {
			if team.data[svIndex].result != 1 {
				team.data[svIndex].numAtt++
			}
		}

		if svFlag == "ACCESSED" {
			if team.data[svIndex].result != 1 {
				team.penalty += team.data[svIndex].numAtt * 20
				team.penalty += int(evTime.Sub(starting).Minutes())
				team.hacked++
				team.data[svIndex].result = 1
			}
		}

		teams[tName] = team
	}

	var sortedTeams []teamData
	for _, team := range teams {
		sortedTeams = append(sortedTeams, team)
	}

	sort.SliceStable(sortedTeams, func(i, j int) bool {
		if sortedTeams[i].hacked != sortedTeams[j].hacked {
			return sortedTeams[i].hacked > sortedTeams[j].hacked
		}
		if sortedTeams[i].penalty != sortedTeams[j].penalty {
			return sortedTeams[i].penalty < sortedTeams[j].penalty
		}
		return sortedTeams[i].name < sortedTeams[j].name
	})

	prevRank := 1
	for i, team := range sortedTeams {
		if i > 0 && (team.hacked != sortedTeams[i-1].hacked || team.penalty != sortedTeams[i-1].penalty) {
			prevRank = i + 1
		}

		fmt.Printf("%d %s %d %d\n", prevRank, team.name, team.hacked, team.penalty)
	}
}
