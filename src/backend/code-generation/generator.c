#include "../support/logger.h"
#include "generator.h"
#include <string.h>
#include "../support/chartType1Singleton.h"
#include <stdio.h>
#include <stdlib.h>
#include "../support/chartType2Singleton.h"

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


static void writeChartType1(FILE * file){
	char graphName[DATASETSIZE];
	char yAxis[DATASETSIZE];
	char xAxis[DATASETSIZE];

	getChartType1GraphName(graphName);
	char * outputXaxis;
	if ( getChartType1XAxisLabel(xAxis)){
		outputXaxis = xAxis;
	} else {
		outputXaxis = "X-Axis";
	}
	char * outputYaxis;
	if (getChartType1YAxisLabel(yAxis)){
		outputYaxis = yAxis;
	} else {
		outputYaxis = "Y-Axis";
	}

	char color[DATASETSIZE];
	char * colorOutput;


	if ( getChartType1Color(color)){
			colorOutput = color;
		} else {
			colorOutput = "blue";
		}

	if ( getChartType1State() == SCATTERTYPE){
		char coordinates[DATASETSIZE];
		getDataAsScatter(coordinates);
		
		

		fprintf(file,"new Chart(ctx, { type: 'scatter' ,");
		fprintf(file," data: { datasets: [{ label: '%s', data: [ %s ], pointBackgroundColor: '%s', pointBorderColor: '%s', pointRadius: 5, pointHoverRadius: 8, }]}",graphName,coordinates, colorOutput,colorOutput);
		fprintf(file,",options: { title: { display: true, text: '%s' }, scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: '%s' } },y: { type: 'linear',position: 'left', title: { display: true, text: '%s' } } } }});",graphName,outputXaxis,outputYaxis);
	} else {		
		char xAxisData[DATASETSIZE];
		char yAxisData[DATASETSIZE];
		getXandYAxisData(xAxisData,yAxisData);
		fprintf(file,"new Chart(ctx, { type: 'line' ,");
		fprintf(file," data: { labels: [ %s ], datasets: [{ label: 'Data', data: [ %s ], backgroundColor: 'rgba(0, 123, 255, 0.5)', borderColor: '%s', borderWidth: 1, }]},",xAxisData,yAxisData,colorOutput);
		fprintf(file,"options: { title: { display: true, text: '%s' }, scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: '%s' } },y: { type: 'linear',position: 'left', title: { display: true, text: '%s' } } } }});",graphName,outputXaxis,outputYaxis);
	}

}



void Generator(int isChartType1) {
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
	if (isChartType1){
		writeChartType1(file);
	} else {
		writeChartType2(file);
	}


	//tag script js cierre
	fprintf(file,"</script></body></html>");
    
    // Close the file
    fclose(file);
    
    return;
}
