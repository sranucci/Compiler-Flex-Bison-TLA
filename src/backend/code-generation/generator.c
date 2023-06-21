#include "../support/logger.h"
#include "generator.h"
#include <string.h>
#include "../domain-specific/calculator.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Implementación de "generator.h".
 */
#define DATASETSIZE 2048


static void writeChartType2(FILE * file){
	char numberDataSet[DATASETSIZE];
	char labelsDataSet[DATASETSIZE];
	char colorDataSet[DATASETSIZE];
	char graphName[DATASETSIZE];
	char graphType[DATASETSIZE];
	getChartType(graphType);
	getGraphName(graphName);
	outputBarNumbers(numberDataSet);
	outputLabels(labelsDataSet);
	outputColors(colorDataSet);
	if ( strcmp(graphType,"bar") == 0){
		fprintf(file,"var myChart = new Chart(ctx, {type: '%s',data: { labels: %s",graphType,labelsDataSet);
		fprintf(file,",datasets: [{label: %s,",graphName);
		fprintf(file," data: %s,",numberDataSet);
		fprintf(file,"backgroundColor: %s ",colorDataSet);
		fprintf(file," }]}});");
	} else {
		fprintf(file,"var data = { labels: %s ,datasets: [{ data: %s,backgroundColor: %s}]};",labelsDataSet,numberDataSet,colorDataSet);
		fprintf(file,"var myChart = new Chart(ctx, { type: 'pie', data: data, options: { plugins: { title: { display: true, text: %s, fontSize: 16 } } }});",graphName);
	}
}




void Generator() {
	FILE *file;
    char *filename = "index.html";
    
    // Open the file in write mode ("w")
    file = fopen(filename, "w");
    
    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

	char * startHTML = "<!DOCTYPE html> <html> <head> </head><body> <canvas id=\"myChart\"></canvas><script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>";
	fprintf(file,"%s",startHTML);

	//tag script js apertura
	fprintf(file,"<script>");

	fprintf(file,"var ctx = document.getElementById('myChart').getContext('2d');");
	writeChartType2(file);



	//tag script js cierre
	fprintf(file,"</script></body></html>");
    
    // Close the file
    fclose(file);
    
    return;
}
